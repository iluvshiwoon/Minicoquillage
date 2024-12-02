/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:40:29 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 04:13:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_reset_fd(t_exec exec)
{
	dup2(exec.og_stdin, STDIN_FILENO);
	dup2(exec.og_stdout, STDOUT_FILENO);
}

int	_call_builtin(t_mini *mini, char **globbed, t_exec exec)
{
	if (ft_strncmp(globbed[0], "echo", _max_len(ft_strlen(globbed[0]),
				ft_strlen("echo"))) == 0)
		return (mini_echo(globbed));
	else if (ft_strncmp(globbed[0], "cd", _max_len(ft_strlen(globbed[0]),
				ft_strlen("cd"))) == 0)
		return (mini_cd(mini, globbed));
	else if (ft_strncmp(globbed[0], "pwd", _max_len(ft_strlen(globbed[0]),
				ft_strlen("pwd"))) == 0)
		return (mini_pwd());
	else if (ft_strncmp(globbed[0], "export", _max_len(ft_strlen(globbed[0]),
				ft_strlen("export"))) == 0)
		return (mini_export(mini, globbed));
	else if (ft_strncmp(globbed[0], "unset", _max_len(ft_strlen(globbed[0]),
				ft_strlen("unset"))) == 0)
		return (mini_unset(mini, globbed));
	else if (ft_strncmp(globbed[0], "env", _max_len(ft_strlen(globbed[0]),
				ft_strlen("env"))) == 0)
		return (mini_env(mini->envp));
	else if (ft_strncmp(globbed[0], "exit", _max_len(ft_strlen(globbed[0]),
				ft_strlen("exit"))) == 0)
		return (mini_exit(mini, globbed, exec));
	return (42);
}

void	__dup(t_mini *mini, t_exec * exec)
{
	t_double_link_node	*node;
	int					*fd;

	node = wrap_malloc(mini,  sizeof(*node));
	fd = wrap_malloc(mini,  sizeof(*fd));
	node->data = fd;
	*fd = dup(STDIN_FILENO);
	mini->fds->pf_insert_end(mini->fds, node);
	exec->og_stdin = *fd;
	node = wrap_malloc(mini,  sizeof(*node));
	fd = wrap_malloc(mini,  sizeof(*fd));
	node->data = fd;
	*fd = dup(STDOUT_FILENO);
	mini->fds->pf_insert_end(mini->fds, node);
	exec->og_stdout = *fd;
}
