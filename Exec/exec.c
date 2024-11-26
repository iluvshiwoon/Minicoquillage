/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 15:53:06 by kgriset          ###   ########.fr       */
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

int _call_builtin(t_mini * mini, char ** globbed, t_exec exec)
{
    if (ft_strncmp(globbed[0], "echo", _max_len(ft_strlen(globbed[0]),ft_strlen("echo"))) == 0)
        return(mini_echo(globbed));
    else if (ft_strncmp(globbed[0], "cd", _max_len(ft_strlen(globbed[0]),ft_strlen("cd"))) == 0)
        return(mini_cd(&mini->heap, globbed,&mini->envp));
    else if (ft_strncmp(globbed[0], "pwd", _max_len(ft_strlen(globbed[0]),ft_strlen("pwd"))) == 0)
        return(mini_pwd());
    else if (ft_strncmp(globbed[0], "export", _max_len(ft_strlen(globbed[0]),ft_strlen("export"))) == 0)
        return(mini_export(&mini->heap,globbed,&mini->envp));
    else if (ft_strncmp(globbed[0], "unset", _max_len(ft_strlen(globbed[0]),ft_strlen("unset"))) == 0)
        return(mini_unset(&mini->heap,globbed,&mini->envp));
    else if (ft_strncmp(globbed[0], "env", _max_len(ft_strlen(globbed[0]),ft_strlen("env"))) == 0)
        return(mini_env(mini->envp));
    else if (ft_strncmp(globbed[0], "exit", _max_len(ft_strlen(globbed[0]),ft_strlen("exit"))) == 0)
        return(mini_exit(&mini->heap, globbed, mini->status, exec.og_stdin, exec.og_stdout));
    return 42; 
}

int _exec_node(t_mini * mini, char ** globbed)
{
    pid_t pid;
    int wstatus;
    char * path;
    int err;
    struct termios ogi_term;

    wstatus = mini->status;
    if (!globbed || !(globbed[0]))
        return (0);
    path = get_path(&mini->heap,mini->envp, &wstatus,globbed[0]);
    if (!path)
        return(wstatus);
    tcgetattr(STDIN_FILENO, &ogi_term);
    pid = fork();
    if (pid < 0)
        return(perror("pid"),error_exit("fork failed\n",&mini->heap_allocated),4);
    if (pid == 0)
    {
        execve(path,globbed,mini->envp);
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
                error_exit(strerror(errno),&mini->heap_allocated);
        }
        else if (WIFEXITED(wstatus))
            return (WEXITSTATUS(wstatus));
        else if (WIFSIGNALED(wstatus))
            return (tcsetattr(STDIN_FILENO,TCSANOW,&ogi_term),128 + WTERMSIG(wstatus));
    }
    return (error_exit("_exec_node\n",&mini->heap_allocated),42);
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

int	_pipeline(t_mini * mini,t_ast_node * first_node,t_exec exec)
{
    int i;
    pid_t * pid;
    int (*pipefd)[2];
    int  pipe_nb;
    t_ast_node * left;
    t_parser_node * p_node;
    char * path;
    char ** globbed;

    i = -1;
    exec.skip = 0;
    _count_pipe(&mini->heap,&pipefd,&pipe_nb,first_node);
    pid = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.exec,sizeof(pid_t)*(pipe_nb + 1));
    while (++i < pipe_nb + 1)
    {
        pid[i] = fork();// same as for open wrapper for failure; 
        if (pid[i] == 0)
        {
            _close(exec.og_stdin);
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
            redirect(mini, &exec, first_node);
            _close(exec.og_stdout);
            if (is_op(p_node->ops) && !exec.skip)
            {
                _exec_tree(mini,left);
                p_node = first_node->data;
                if (p_node->atom && p_node->atom->in_fd)
                    _close(p_node->atom->in_fd);
                if (p_node->atom && p_node->atom->out_fd)
                    _close(p_node->atom->out_fd);
                p_node = left->data;
            }
            else if (!exec.skip)
            {
                exec.og_stdin = 0;
                exec.og_stdout = 0;
                globbed = _glob_args(&mini->heap,_expand(mini, p_node->atom->args));
                if (check_builtin(&mini->heap, globbed[0]))
                    mini->status = _call_builtin(mini, globbed,exec);
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
            exit((mini->status + 256)%256);
        }
        else
        {
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
    }
    i = -1;
    while (++i < pipe_nb + 1)
    {
        while (1)
        {
            int err = waitpid(pid[i], &mini->status,0);
            if (err == -1)
            {
                if (errno == EINTR)
                    continue;
                else
                    error_exit(strerror(errno),&mini->heap_allocated);
            }
            else if (WIFEXITED(mini->status) || WIFSIGNALED(mini->status))
                break;
        }
    }
    if (WIFEXITED(mini->status))
        return (WEXITSTATUS(mini->status));
    else if (WIFSIGNALED(mini->status))
        return (128 + WTERMSIG(mini->status));
    return (error_exit("pipeline failure\n",&mini->heap_allocated),999);
}
