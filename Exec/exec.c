/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/09 19:29:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
// add globbing and expand to pipeline;
// heredoc handle expansion (logic & link list for env for ez edit from export unset ...)
// signal
// managing term var (ex vim killed...)
// Check builtins
// TEST: script to test path / exec / expansion with echo and export / expansion in heredoc 
// bonus change arrow color depending on exit status;
// edit readme to add tricky point to remember for future evaluation
void	_exec_tree(t_heap * heap,t_ast_node * first_node, char ** envp);

void execution(t_heap_allocated * heap_allocated, t_ast * ast, char * line, char ** envp)
{
    t_heap heap;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->exec;
    heredoc(&heap, ast->first_node);
    _exec_tree(&heap, ast->first_node, envp);
    add_history(line);
    clean_heredoc(&heap, ast->first_node);
}

int _exec_node(t_heap * heap, t_parser_node * p_node, char ** envp, int status)
{
    pid_t pid;
    int wstatus;
    char * path;
    char ** globbed;

    globbed = _glob_args(heap,_expand(heap, p_node->atom->args, envp, status));
    path = get_path(heap, &wstatus,globbed[0]);
    if (!path)
        return(wstatus);
    pid = fork();
    if (pid < 0)
        return(perror("pid"),error_exit("fork failed\n",heap->heap_allocated),4);
    if (pid == 0)
    {
        execve(path,globbed,envp);
        perror("execve");
    }
    waitpid(pid, &wstatus,0);
    if (WIFEXITED(wstatus))
        return (WEXITSTATUS(wstatus));
    return (error_exit("_exec_node\n",heap->heap_allocated),42);
}

void    _error(char * error, int * skip, int * status, char * filename)
{
    *skip = 1;
    *status = 1;
    printf(error,filename);
}

int     _stdin(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp)
{
    int i = -1;
    t_expanded * expanded;
    char * globbed;
    t_glob * _globbed;

    expanded = _expand(heap, atom->std_in, envp, *status);
    while (expanded->value[++i])
    {
        if (_count_glob(heap, expanded->value[i],expanded->litteral[i]) > 1)
            return(_error("minicoquillage: %s: ambiguous redirect\n",skip,status,expanded->value[i]),1);
        else
        {
            _globbed = glob(heap, expanded->value[i], expanded->litteral[i]); 
            globbed = expanded->value[i];
            if (_globbed)
                globbed = _globbed->file;
        }
        if (access(globbed,F_OK))
            return (_error("minicoquillage: %s: No such file or directory\n", skip, status, globbed),1);
        else if(access(globbed,R_OK)) 
            return (_error("minicoquillage: %s: Permission denied\n", skip, status, globbed),1);
        else if (!atom->std_in[i+1] && atom->heredoc == false)
            atom->in_fd = open(globbed, O_RDONLY);
    }
    if (atom->heredoc)
    {
        close(atom->in_fd);
        atom->in_fd = open(atom->file_heredoc, O_RDONLY);
    }
    if (atom->in_fd)
        dup2(atom->in_fd,STDIN_FILENO);
    return (0);
}

int     _stdout(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp)
{
    int i = -1;
    t_expanded * expanded;
    char * globbed;
    t_glob * _globbed;
    struct stat sb;

    expanded = _expand(heap, atom->std_out, envp, *status);
    while (expanded->value[++i])
    {
        if (_count_glob(heap, expanded->value[i],expanded->litteral[i]) > 1)
            return(_error("minicoquillage: %s: ambiguous redirect\n",skip,status,expanded->value[i]),1);
        else
        {
            _globbed = glob(heap, expanded->value[i], expanded->litteral[i]); 
            globbed = expanded->value[i];
            if (_globbed)
                globbed = _globbed->file;
        }
        if (stat(globbed, &sb) == -1 && errno == EACCES)
            return(_error("minicoquillage: %s: Permission denied\n",skip,status,globbed),1);
        else if (stat(globbed, &sb) == -1 && errno == ENOENT)
        {
            atom->out_fd = open(globbed, O_EXCL | O_CREAT , S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
            close(atom->out_fd);
        }
        else if (access(globbed,W_OK))
            return(_error("minicoquillage: %s: Permission denied\n",skip,status,globbed),1);
        else if (S_ISDIR(sb.st_mode))
            return(_error("minicoquillage: %s: Is a directory\n",skip,status,globbed),1);
        else if (access(globbed,W_OK) == 0 && atom->append[i] == false)
        {
            atom->out_fd = open(globbed, O_WRONLY | O_TRUNC);
            close(atom->out_fd);
        }
        if (!expanded->value[i+1])
        {
            if (atom->append[i])
                atom->out_fd = open(globbed, O_WRONLY | O_APPEND);
            else
                atom->out_fd = open(globbed, O_WRONLY);
        }
        if (atom->out_fd == -1)
            perror("open"); // FIXME redirection fail ? skip ?
    }
    if (atom->out_fd)
        dup2(atom->out_fd,STDOUT_FILENO);
    return (0);
}

void    _redirect(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp)
{
    _stdin(heap, skip, status, atom, envp); 
    _stdout(heap, skip, status, atom, envp);
}

void    redirect(t_heap * heap, int * skip, int * status, t_ast_node * first_node, char ** envp)
{
    t_parser_node * p_node;

    p_node = first_node->left->data;
    if (is_op(p_node->ops))
    {
        p_node = first_node->data;
        if (p_node->atom)
            _redirect(heap, skip, status, p_node->atom, envp);    
    }
    else if (p_node->atom)
        _redirect(heap, skip, status, p_node->atom, envp);
}

void _reset_fd(int og_stdin, int og_stdout)
{
    dup2(og_stdin, STDIN_FILENO);
    dup2(og_stdout, STDOUT_FILENO);
}

void    _count_pipe(t_heap * heap, int (**pipefd)[2], int * pipe_nb, t_ast_node * first_node)
{
    t_parser_node * p_node;
    int i;

    *pipe_nb = 0;
    i = -1;
    while(first_node && first_node->left)
    {
        p_node = first_node->data;
        if (p_node->ops && p_node->ops == PIPE)
            (*pipe_nb)++;
        else
            break;
        first_node = first_node->right;
    }
    *pipefd = wrap_malloc(heap->heap_allocated,heap->list,sizeof(**pipefd) * *pipe_nb);
    while (++i < *pipe_nb)
    {
        if(pipe((*pipefd)[i]) == -1) // FIXME
            perror("pipe");
    }
}

int	_pipeline(t_heap * heap,t_ast_node * first_node, char ** envp)
{
    int i;
    int wstatus;
    pid_t pid;
    int (*pipefd)[2];
    int pipe_nb;
    t_ast_node * left;
    t_parser_node * p_node;
    char * path;
    int status;
    int skip;

    i = -1;
    skip = 0;
    status = 0;
    _count_pipe(heap,&pipefd,&pipe_nb,first_node);
    while (++i < pipe_nb + 1)
    {
        pid = fork();// same as for open wrapper for failure; 
        if (pid == 0)
        {
            int j; 
            j = -1;
            if (i == 0)
            {
                while (++j < pipe_nb)
                {
                    if (j == 0)
                    {
                        dup2(pipefd[j][1],STDOUT_FILENO);
                        close(pipefd[j][1]);
                    }
                    else
                        close(pipefd[j][1]);
                    close(pipefd[j][0]);
                }
            }
            else if (i == pipe_nb)
            {
                while (++j < pipe_nb)
                {
                    if (j == i - 1)
                    {
                        dup2(pipefd[i-1][0], STDIN_FILENO);
                        close(pipefd[i-1][0]);
                    }
                    else
                        close(pipefd[j][0]);
                    close(pipefd[j][1]);
                }
            }
            else 
            {
                while (++j < pipe_nb)
                {
                    if (j == i - 1)
                    {
                        dup2(pipefd[i-1][0],STDIN_FILENO);
                        close(pipefd[i-1][0]);
                    }
                    else
                        close(pipefd[j][0]);
                    if (j == i)
                    {
                        dup2(pipefd[i][1],STDOUT_FILENO);
                        close(pipefd[i][1]);
                    }
                    else
                        close(pipefd[j][1]);
                }
            }
            j = -1;
            while (++j < i)
                first_node = first_node->right; 
            left = first_node->left;
            p_node = left->data;
            redirect(heap, &skip, &status, first_node, envp);
            if (is_op(p_node->ops))
            {
                _exec_tree(heap,left, envp);
                p_node = first_node->data;
                if (p_node->atom && p_node->atom->in_fd)
                    close(p_node->atom->in_fd);
                if (p_node->atom && p_node->atom->out_fd)
                    close(p_node->atom->out_fd);
                p_node = left->data;
            }
            else 
            {
                path = get_path(heap,&status,p_node->atom->cmd);
                // printf("%d\n",status);
                if (path)
                {
                    // printf("%s\n",path);
                    execve(path,p_node->atom->args,envp);
                    // status = _exec_node(heap,path,p_node,envp);
                    if (p_node->atom && p_node->atom->in_fd)
                        close(p_node->atom->in_fd);
                    if (p_node->atom && p_node->atom->out_fd)
                        close(p_node->atom->out_fd);
                }
            }   
            free_heap(heap->heap_allocated);
            exit(status);
        }
    }
    i = -1;
    while (++i < pipe_nb + 1)
    {
        waitpid(-1, &wstatus,0);
        if (i == 0)
            close(pipefd[i][1]);
        else if (i == pipe_nb)
            close (pipefd[i - 1][0]);
        else
        {
            close (pipefd[i - 1][0]);
            close (pipefd[i][1]);
        }
    }
    if (WIFEXITED(wstatus))
        return (/* printf("%d\n",WEXITSTATUS(wstatus)), */WEXITSTATUS(wstatus));
    return (error_exit("pipeline failure\n",heap->heap_allocated),42);
}

void	_exec_tree(t_heap * heap,t_ast_node * first_node, char ** envp)
{
    t_ast_node * left;
    t_parser_node * p_node;
    static int status;
    int skip;
    int og_stdin;
    int og_stdout;

    skip = 0;
    while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = first_node->data;
        if (p_node->ops && p_node->ops == PIPE)
        {
            skip = 1;
            status = _pipeline(heap,first_node,envp);
            while(p_node->ops && p_node->ops == PIPE)
            {
                first_node = first_node->right;
                p_node = first_node->data;
            }
        }
        og_stdin = dup(STDIN_FILENO);
        og_stdout = dup(STDOUT_FILENO);
        p_node = left->data;
        if (!skip)
            redirect(heap, &skip, &status, first_node, envp);
        if (is_op(p_node->ops) && !skip)
        {
            _exec_tree(heap,left, envp);
            p_node = first_node->data;
            if (p_node->atom && p_node->atom->in_fd)
                close(p_node->atom->in_fd);
            if (p_node->atom && p_node->atom->out_fd)
                close(p_node->atom->out_fd);
            p_node = left->data;
        }
        else if (!skip) 
        {
            status = _exec_node(heap,p_node,envp, status);
            if (p_node->atom && p_node->atom->in_fd)
                close(p_node->atom->in_fd);
            if (p_node->atom && p_node->atom->out_fd)
                close(p_node->atom->out_fd);
        }
        p_node = first_node->data;
        if(p_node->ops)
        {
            if (p_node->ops == AND && status)
                skip = 1;
            else if (p_node->ops && p_node->ops != PIPE)
                skip = 0;
        }
        _reset_fd(og_stdin, og_stdout);
        close(og_stdin);
        close(og_stdout);
        first_node = first_node->right;
	}
}
