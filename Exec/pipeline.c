/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 16:43:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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

void    _close_pipe(int pipe_nb, int (*pipefd)[2])
{
    int j;

    j = -1;
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

void    _close_pipe1(int pipe_nb, int (*pipefd)[2], int i)
{
    int j;

    j = -1;
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

void    _close_pipe2(int pipe_nb, int (*pipefd)[2], int i)
{
    int j;

    j = -1;
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
                _close_pipe(pipe_nb,pipefd);
            else if (i == pipe_nb)
                _close_pipe1(pipe_nb,pipefd,i);
            else 
                _close_pipe2(pipe_nb,pipefd,i);
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
