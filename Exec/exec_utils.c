/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:40:29 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 16:13:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
		return (mini_cd(&mini->heap, globbed, &mini->envp));
	else if (ft_strncmp(globbed[0], "pwd", _max_len(ft_strlen(globbed[0]),
				ft_strlen("pwd"))) == 0)
		return (mini_pwd());
	else if (ft_strncmp(globbed[0], "export", _max_len(ft_strlen(globbed[0]),
				ft_strlen("export"))) == 0)
		return (mini_export(&mini->heap, globbed, &mini->envp));
	else if (ft_strncmp(globbed[0], "unset", _max_len(ft_strlen(globbed[0]),
				ft_strlen("unset"))) == 0)
		return (mini_unset(&mini->heap, globbed, &mini->envp));
	else if (ft_strncmp(globbed[0], "env", _max_len(ft_strlen(globbed[0]),
				ft_strlen("env"))) == 0)
		return (mini_env(mini->envp));
	else if (ft_strncmp(globbed[0], "exit", _max_len(ft_strlen(globbed[0]),
				ft_strlen("exit"))) == 0)
		return (mini_exit(&mini->heap, globbed, mini->status, exec.og_stdin,
				exec.og_stdout));
	return (42);
}
