/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/28 22:44:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
// heredoc handle expansion (logic & link list for env for ez edit from export unset ...)
// edit readme to add tricky point to remember for future evaluation
// bitshifting for correct permisssion when recreating file from stat
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

int _exec_node(t_heap * heap, char * path, t_parser_node * p_node, char ** envp)
{
    pid_t pid;
    int wstatus;

    pid = fork();
    if (pid < 0)
        return(perror(NULL),error_exit("fork failed\n",heap->heap_allocated),4);
    if (pid == 0)
    {
        execve(path,p_node->atom->args,envp);
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

int     _stdin(int * skip, int * status, t_atom * atom)
{
    int i = -1;

    while (atom->std_in[++i])
    {
        if (access(atom->std_in[i],F_OK))
            return (_error("minicoquillage: %s: No such file or directory\n", skip, status, atom->std_in[i]),1);
        else if(access(atom->std_in[i],R_OK)) 
            return (_error("minicoquillage: %s: Permission denied\n", skip, status, atom->std_in[i]),1);
        else if (!atom->std_in[i+1] && atom->heredoc == false)
            atom->in_fd = open(atom->std_in[i], O_RDONLY);
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

mode_t    _mode(mode_t mode,mode_t mask)
{
    return(mode & mask);
}

int     _stdout(int * skip, int * status, t_atom * atom)
{
    int i = -1;
    struct stat sb;
    mode_t mode;

    while (atom->std_out[++i])
    {
        if (stat(atom->std_out[i], &sb) == -1 && errno == EACCES)
            return(_error("minicoquillage: %s: Permission denied\n",skip,status,atom->std_out[i]),1);
        else if (stat(atom->std_out[i], &sb) == -1 && errno == ENOENT)
        {
            atom->out_fd = open(atom->std_out[i], O_EXCL | O_CREAT , S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
            close(atom->out_fd);
        }
        else if (access(atom->std_out[i],W_OK))
            return(_error("minicoquillage: %s: Permission denied\n",skip,status,atom->std_out[i]),1);
        else if (S_ISDIR(sb.st_mode))
            return(_error("minicoquillage: %s: Is a directory\n",skip,status,atom->std_out[i]),1);
        else if (access(atom->std_out[i],W_OK) == 0 && atom->append[i] == false)
        {
            mode = sb.st_mode;
            if (unlink(atom->std_out[i]))
                perror("unlink"); // FIXME what to do here?
            atom->out_fd = open(atom->std_out[i], O_EXCL | O_CREAT ,\
_mode(mode,S_IRUSR) | _mode(mode,S_IWUSR) |_mode(mode,S_IXUSR)|\
_mode(mode,S_IRGRP) |_mode(mode,S_IWGRP) |_mode(mode,S_IXGRP) |\
_mode(mode,S_IROTH)|_mode(mode,S_IWOTH)|_mode(mode,S_IXOTH)|\
_mode(mode,S_ISUID)|_mode(mode,S_ISGID)|_mode(mode,S_ISVTX));
            close(atom->out_fd);
        }
        if (!atom->std_out[i+1])
            atom->out_fd = open(atom->std_out[i], O_WRONLY);
        if (atom->out_fd == -1)
            perror("open"); // FIXME redirection fail ? skip ?
    }
    if (atom->out_fd)
        dup2(atom->out_fd,STDOUT_FILENO);
    return (0);
}

void    _redirect(int * skip, int * status, t_atom * atom)
{
    _stdin(skip, status, atom); 
    _stdout(skip, status, atom);
}

void    redirect(int * skip, int * status, t_ast_node * first_node)
{
    t_parser_node * p_node;

    p_node = first_node->left->data;
    if (is_op(p_node->ops))
    {
        p_node = first_node->data;
        if (p_node->atom)
            _redirect(skip, status, p_node->atom);    
    }
    else if (p_node->atom)
        _redirect(skip, status, p_node->atom);
}

void _reset_fd(int og_stdin, int og_stdout)
{
    dup2(og_stdin, STDIN_FILENO);
    dup2(og_stdout, STDOUT_FILENO);
}

void	_exec_tree(t_heap * heap,t_ast_node * first_node, char ** envp)
{
    t_ast_node * left;
    t_parser_node * p_node;
    char * path;
    static int status;
    int skip;
    int og_stdin;
    int og_stdout;

    skip = 0;
    og_stdin = dup(STDIN_FILENO);
    og_stdout = dup(STDOUT_FILENO);
	while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = left->data;
        if (!skip)
            redirect(&skip, &status, first_node);
        if (is_op(p_node->ops) && !skip)
            _exec_tree(heap,left, envp);
        else 
        {
            path = get_path(heap,p_node->atom->cmd);
            if (path && !skip)
            {
                status = _exec_node(heap,path,p_node,envp);
                if (p_node->atom->in_fd)
                    close(p_node->atom->in_fd);
                if (p_node->atom->out_fd)
                    close(p_node->atom->out_fd);
            }
            else if (!path)
                status = 127;
            // printf("%s ",p_node->atom->cmd);
            // print_t_options(p_node->atom);
            // print_t_args(p_node->atom);
            // if (p_node->atom->heredoc)
            // {
            //     print_t_stdin(p_node->atom);
            //     print_t_heredoc(p_node->atom);
            // }
            // else 
            // {
            //     print_t_heredoc(p_node->atom);
            //     print_t_stdin(p_node->atom);
            // }
            // print_t_stdout(p_node->atom);
        }
        p_node = first_node->data;
        if(p_node->ops)
        {
            if (p_node->ops == AND && status)
                skip = 1;
            else if (p_node->ops)
                skip = 0;
            // if (p_node->atom)
            // {
            //     if (p_node->atom->heredoc)
            //     {
            //         print_t_stdin(p_node->atom);
            //         print_t_heredoc(p_node->atom);
            //     }
            //     else 
            //     {
            //         print_t_heredoc(p_node->atom);
            //         print_t_stdin(p_node->atom);
            //     }
            //     print_t_stdout(p_node->atom);
            // }
            // if (p_node->ops != EOE)
            //     printf("%s ",type[p_node->ops]);
        }
        _reset_fd(og_stdin, og_stdout);
        first_node = first_node->right;
	}
    close(og_stdin);
    close(og_stdout);
}
