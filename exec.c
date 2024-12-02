/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:05:37 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	execution(t_mini *mini, t_ast *ast)
{
	mini->list = mini->heap_allocated.exec;
	heredoc(mini, ast->first_node);
	if (g_signal == SIGINT)
	{
		clean_heredoc(mini, ast->first_node);
		return ;
	}
	g_signal = 999;
	_exec_tree(mini, ast->first_node);
	g_signal = 0;
	if (MODE == INTERACTIVE)
		add_history(mini->control.line);
	clean_heredoc(mini, ast->first_node);
	close_fds(mini->fds);
}

int	__exec_node(t_mini *mini, pid_t pid, struct termios ogi_term)
{
	int	err;

	while (1)
	{
		err = waitpid(pid, &mini->status, 0);
		if (err == -1)
		{
			if (errno == EINTR)
				continue ;
			else
				error_exit(strerror(errno), mini);
		}
		else if (WIFEXITED(mini->status))
			return (WEXITSTATUS(mini->status));
		else if (WIFSIGNALED(mini->status))
			return (tcsetattr(STDIN_FILENO, TCSANOW, &ogi_term), 128
				+ WTERMSIG(mini->status));
	}
	return (error_exit("_exec_node\n", mini), 42);
}

int	_exec_node(t_mini *mini, char **globbed)
{
	pid_t			pid;
	char			*path;
	struct termios	ogi_term;

	if (!globbed || !(globbed[0]))
		return (0);
	path = get_path(mini, globbed[0]);
	if (!path)
		return (mini->status);
	tcgetattr(STDIN_FILENO, &ogi_term);
	pid = fork();
	if (pid < 0)
		return (perror("pid"), error_exit("fork failed\n", mini), 4);
	if (pid == 0)
	{
        close_fds(mini->fds);
		execve(path, globbed, mini->envp);
		perror("execve");
	}
	return (__exec_node(mini, pid, ogi_term));
}
