/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/21 01:16:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
// managing term var (ex vim killed...)
// TEST: script to test path / exec / expansion with echo and export / expansion in heredoc 
//
// BONUS
// bonus change arrow color depending on exit status;
// heredoc handle expansion (logic & link list for env for ez edit from export unset ...)
//
// EVAL
// edit readme to add tricky point to remember for future evaluation
void	_exec_tree(t_mini * mini, t_ast_node * first_node);

void execution(t_mini * mini, t_ast * ast)
{
    mini->heap.heap_allocated = &mini->heap_allocated;
    mini->heap.list = mini->heap_allocated.exec;
    mini->heap.env = mini->heap_allocated.env;
    heredoc(&mini->heap, ast->first_node);
    if (g_signal == SIGINT)
    {
        clean_heredoc(&mini->heap, ast->first_node);
        return;
    }
    g_signal = 999;
    _exec_tree(mini, ast->first_node);
    g_signal = 0;
    if (MODE == INTERACTIVE)
        add_history(mini->control.line);
    clean_heredoc(&mini->heap, ast->first_node);
}

int _call_builtin(t_heap * heap, char ** globbed, char *** envp, int status, int og_stdin, int og_stdout)
{
    if (ft_strncmp(globbed[0], "echo", _max_len(ft_strlen(globbed[0]),ft_strlen("echo"))) == 0)
        return(mini_echo(globbed));
    else if (ft_strncmp(globbed[0], "cd", _max_len(ft_strlen(globbed[0]),ft_strlen("cd"))) == 0)
        return(mini_cd(heap, globbed,envp));
    else if (ft_strncmp(globbed[0], "pwd", _max_len(ft_strlen(globbed[0]),ft_strlen("pwd"))) == 0)
        return(mini_pwd());
    else if (ft_strncmp(globbed[0], "export", _max_len(ft_strlen(globbed[0]),ft_strlen("export"))) == 0)
        return(mini_export(heap,globbed,envp));
    else if (ft_strncmp(globbed[0], "unset", _max_len(ft_strlen(globbed[0]),ft_strlen("unset"))) == 0)
        return(mini_unset(heap,globbed,envp));
    else if (ft_strncmp(globbed[0], "env", _max_len(ft_strlen(globbed[0]),ft_strlen("env"))) == 0)
        return(mini_env(*envp));
    else if (ft_strncmp(globbed[0], "exit", _max_len(ft_strlen(globbed[0]),ft_strlen("exit"))) == 0)
        return(mini_exit(heap, globbed, status, og_stdin, og_stdout));
    return 42; 
}

int _exec_node(t_heap * heap, char ** globbed, char *** envp, int status)
{
    pid_t pid;
    int wstatus;
    char * path;
    int err;
    struct termios ogi_term;

    wstatus = status;
    if (!globbed || !(globbed[0]))
        return (0);
    path = get_path(heap,*envp, &wstatus,globbed[0]);
    if (!path)
        return(wstatus);
    tcgetattr(STDIN_FILENO, &ogi_term);
    pid = fork();
    if (pid < 0)
        return(perror("pid"),error_exit("fork failed\n",heap->heap_allocated),4);
    if (pid == 0)
    {
        execve(path,globbed,*envp);
        perror("execve");
    }
    while (1)
    {
        err = waitpid(pid, &wstatus,0);
        if (err == -1)
        {
            if (errno == EINTR)
                continue;
            else
                error_exit(strerror(errno),heap->heap_allocated);
        }
        else if (WIFEXITED(wstatus))
            return (WEXITSTATUS(wstatus));
        else if (WIFSIGNALED(wstatus))
            return (tcsetattr(STDIN_FILENO,TCSANOW,&ogi_term),128 + WTERMSIG(wstatus));
    }
    return (error_exit("_exec_node\n",heap->heap_allocated),42);
}

void    _error(char * error, int * skip, int * status, char * filename, int err_status)
{
    *skip = 1;
    *status = err_status;
    printf(error,filename);
}

int     _stdin(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp, int og_stdout)
{
    int i = -1;
    t_expanded * expanded;
    char * globbed;
    t_glob * _globbed;

    expanded = _expand(heap, atom->std_in, envp, *status);
    while (expanded->value[++i])
    {
        if (_count_glob(heap, expanded->value[i],expanded->litteral[i]) > 1)
            return(dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: ambiguous redirect\n",skip,status,expanded->value[i], 1),1);
        else
        {
            _globbed = glob(heap, expanded->value[i], expanded->litteral[i]); 
            globbed = expanded->value[i];
            if (_globbed)
                globbed = _globbed->file;
        }
        if (access(globbed,F_OK))
            return (dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: No such file or directory\n", skip, status, globbed, 1),1);
        else if(access(globbed,R_OK)) 
            return (dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: Permission denied\n", skip, status, globbed, 1),1);
        else if (!atom->std_in[i+1] && atom->heredoc == false)
            atom->in_fd = open(globbed, O_RDONLY);
    }
    if (atom->heredoc)
    {
        _close(atom->in_fd);
        atom->in_fd = open(atom->file_heredoc, O_RDONLY);
    }
    if (atom->in_fd)
        dup2(atom->in_fd,STDIN_FILENO);
    return (0);
}

int     _stdout(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp, int og_stdout)
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
            return(dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: ambiguous redirect\n",skip,status,expanded->value[i], 1),1);
        else
        {
            _globbed = glob(heap, expanded->value[i], expanded->litteral[i]); 
            globbed = expanded->value[i];
            if (_globbed)
                globbed = _globbed->file;
        }
        if (stat(globbed, &sb) == -1 && errno == EACCES)
            return(dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: Permission denied\n",skip,status,globbed, 1),1);
        else if (stat(globbed, &sb) == -1 && errno == ENOENT)
        {
            atom->out_fd = open(globbed, O_EXCL | O_CREAT , S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
            _close(atom->out_fd);
        }
        else if (access(globbed,W_OK))
            return(dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: Permission denied\n",skip,status,globbed, 1),1);
        else if (S_ISDIR(sb.st_mode))
            return(dup2(og_stdout,STDOUT_FILENO),_error("minicoquillage: %s: Is a directory\n",skip,status,globbed, 1),1);
        else if (access(globbed,W_OK) == 0 && atom->append[i] == false)
        {
            atom->out_fd = open(globbed, O_WRONLY | O_TRUNC);
            _close(atom->out_fd);
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

void    _redirect(t_heap * heap, int * skip, int * status, t_atom * atom, char ** envp, int og_stdout)
{
    _stdin(heap, skip, status, atom, envp, og_stdout); 
    _stdout(heap, skip, status, atom, envp, og_stdout);
}

void    redirect(t_heap * heap, int * skip, int * status, t_ast_node * first_node, char ** envp, int og_stdout)
{
    t_parser_node * p_node;

    p_node = first_node->left->data;
    if (is_op(p_node->ops))
    {
        p_node = first_node->data;
        if (p_node->atom)
            _redirect(heap, skip, status, p_node->atom, envp, og_stdout);    
    }
    else if (p_node->atom)
        _redirect(heap, skip, status, p_node->atom, envp, og_stdout);
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

int	_pipeline(t_mini * mini,t_ast_node * first_node, int og_stdin, int og_stdout)
{
    int i;
    int wstatus;
    pid_t pid;
    int (*pipefd)[2];
    int pipe_nb;
    t_ast_node * left;
    t_parser_node * p_node;
    char * path;
    int skip;
    char ** globbed;

    i = -1;
    skip = 0;
    _count_pipe(&mini->heap,&pipefd,&pipe_nb,first_node);
    _close(og_stdin);
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
                        _close(pipefd[j][1]);
                    }
                    else
                        _close(pipefd[j][1]);
                    _close(pipefd[j][0]);
                }
            }
            else if (i == pipe_nb)
            {
                while (++j < pipe_nb)
                {
                    if (j == i - 1)
                    {
                        dup2(pipefd[i-1][0], STDIN_FILENO);
                        _close(pipefd[i-1][0]);
                    }
                    else
                        _close(pipefd[j][0]);
                    _close(pipefd[j][1]);
                }
            }
            else 
            {
                while (++j < pipe_nb)
                {
                    if (j == i - 1)
                    {
                        dup2(pipefd[i-1][0],STDIN_FILENO);
                        _close(pipefd[i-1][0]);
                    }
                    else
                        _close(pipefd[j][0]);
                    if (j == i)
                    {
                        dup2(pipefd[i][1],STDOUT_FILENO);
                        _close(pipefd[i][1]);
                    }
                    else
                        _close(pipefd[j][1]);
                }
            }
            j = -1;
            while (++j < i)
                first_node = first_node->right; 
            left = first_node->left;
            p_node = left->data;
            redirect(&mini->heap, &skip, &mini->status, first_node, mini->envp, og_stdout);
            _close(og_stdout);
            if (is_op(p_node->ops) && !skip)
            {
                _exec_tree(mini,left);
                p_node = first_node->data;
                if (p_node->atom && p_node->atom->in_fd)
                    _close(p_node->atom->in_fd);
                if (p_node->atom && p_node->atom->out_fd)
                    _close(p_node->atom->out_fd);
                p_node = left->data;
            }
            else if (!skip)
            {
                globbed = _glob_args(&mini->heap,_expand(&mini->heap, p_node->atom->args, mini->envp, mini->status));
                if (check_builtin(&mini->heap, globbed[0]))
                    mini->status = _call_builtin(&mini->heap, globbed, &mini->envp, mini->status, 0, 0);
                else
                {
                    path = get_path(&mini->heap,mini->envp,&mini->status,globbed[0]);
                    if (path)
                        execve(path,globbed,mini->envp);
                }
                if (p_node->atom && p_node->atom->in_fd)
                    _close(p_node->atom->in_fd);
                if (p_node->atom && p_node->atom->out_fd)
                    _close(p_node->atom->out_fd);
            }   
            free_heap(&mini->heap_allocated, true);
            exit(mini->status);
        }
    }
    i = -1;
    while (++i < pipe_nb + 1)
    {
        while (1)
        {
            int err = waitpid(-1, &wstatus,0);
            if (err == -1)
            {
                if (errno == EINTR)
                    continue;
                else
                    error_exit(strerror(errno),&mini->heap_allocated);
            }
            else if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus))
                break;
        }
        if (i == 0)
            _close(pipefd[i][1]);
        else if (i == pipe_nb)
            _close (pipefd[i - 1][0]);
        else
        {
            _close (pipefd[i - 1][0]);
            _close (pipefd[i][1]);
        }
    }
    if (WIFEXITED(wstatus))
        return (WEXITSTATUS(wstatus));
    else if (WIFSIGNALED(wstatus))
        return (128 + WTERMSIG(wstatus));
    return (error_exit("pipeline failure\n",&mini->heap_allocated),42);
}

void	_exec_tree(t_mini * mini, t_ast_node * first_node)
{
    t_ast_node * left;
    t_parser_node * p_node;
    int skip;
    int og_stdin;
    int og_stdout;
    char ** globbed;

    og_stdin = dup(STDIN_FILENO);
    og_stdout = dup(STDOUT_FILENO);
    skip = 0;
    // if (heap->signal_mini->status)
    //     mini->status = heap->signal_mini->status;
    while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = first_node->data;
        if (p_node->ops && p_node->ops == PIPE)
        {
            skip = 1;
            mini->status = _pipeline(mini,first_node, og_stdin, og_stdout);
            while(p_node->ops && p_node->ops == PIPE)
            {
                first_node = first_node->right;
                p_node = first_node->data;
            }
        }
        p_node = left->data;
        if (!skip)
            redirect(&mini->heap, &skip, &mini->status, first_node, mini->envp, og_stdout);
        if (is_op(p_node->ops) && !skip)
        {
            _exec_tree(mini,left);
            p_node = first_node->data;
            if (p_node->atom && p_node->atom->in_fd)
                _close(p_node->atom->in_fd);
            if (p_node->atom && p_node->atom->out_fd)
                _close(p_node->atom->out_fd);
            p_node = left->data;
        }
        else if (!skip) 
        {
            globbed = _glob_args(&mini->heap,_expand(&mini->heap, p_node->atom->args, mini->envp, mini->status));
            if (check_builtin(&mini->heap, globbed[0]))
                mini->status = _call_builtin(&mini->heap, globbed, &mini->envp, mini->status, og_stdin, og_stdout);
            else
                mini->status = _exec_node(&mini->heap,globbed,&mini->envp, mini->status);
            if (p_node->atom && p_node->atom->in_fd)
                _close(p_node->atom->in_fd);
            if (p_node->atom && p_node->atom->out_fd)
                _close(p_node->atom->out_fd);
        }
        p_node = first_node->data;
        if(p_node->ops)
        {
            if ((p_node->ops == AND && mini->status) || (p_node->ops == OR && !mini->status))
                skip = 1;
            else if (p_node->ops && p_node->ops != PIPE)
                skip = 0;
        }
        _reset_fd(og_stdin, og_stdout);
        first_node = first_node->right;
	}
    _close(og_stdin);
    _close(og_stdout);
}
