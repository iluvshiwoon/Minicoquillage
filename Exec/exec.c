/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 16:17:18 by kgriset          ###   ########.fr       */
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
