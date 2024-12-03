/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:37:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 15:53:54 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*__get_path(t_mini *mini, char **path, char *cmd)
{
	int		i;
	char	*r_value;

	i = -1;
	while (path[++i])
	{
		r_value = mini_ft_strjoin(mini, path[i], "/");
		r_value = mini_ft_strjoin(mini, r_value, cmd);
		if (access(r_value, F_OK) == 0)
		{
			if (is_dir(r_value))
				return (mini->status = 126, NULL);
			else if (access(r_value, X_OK) == 0)
				return (r_value);
			return (mini->status = 126, ft_printf_fd(STDERR_FILENO, "m\
inicoquillage: %s: Permission denied\n", r_value), NULL);
		}
	}
	return (mini->status = 127, ft_printf_fd(STDERR_FILENO, "minicoquillag\
e: %s", mini_ft_strjoin(mini, cmd, ": command not found\n")), NULL);
}

char	*_get_path(t_mini *mini, char *cmd)
{
	int		i;
	char	**path;
	char	*r_value;

	i = -1;
	r_value = _getenv(mini, "PATH");
	if (!r_value)
		return (mini->status = 127, ft_printf_fd(STDERR_FILENO, "%s",
				mini_ft_strjoin(mini, mini_ft_strjoin(mini, "minicoquillage: ",
						cmd), ": No such file or directory\n")), NULL);
	path = mini_ft_split(mini, r_value, ':');
	while (path[++i])
	{
		r_value = ft_strnstr(path[i], cmd, ft_strlen(path[i]));
		if (r_value && r_value != path[i] && !*(r_value + ft_strlen(cmd)))
		{
			if (access(path[i], X_OK) == 0)
				return (path[i]);
			return (mini->status = 126, ft_printf_fd(STDERR_FILENO, "m\
inicoquillage: %s: Permission denied\n", path[i]), NULL);
		}
	}
	return (__get_path(mini, path, cmd));
}

char	*get_path(t_mini *mini, char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!(cmd[0]))
		return (mini->status = 127, ft_printf_fd(STDERR_FILENO, "minicoquil\
lage: %s", mini_ft_strjoin(mini, cmd, ": command not found\n")), NULL);
	if (is_path(cmd) && access(cmd, F_OK) == -1)
		return (mini->status = 127, ft_printf_fd(STDERR_FILENO, "%s",
				mini_ft_strjoin(mini, mini_ft_strjoin(mini, "minicoquillage: ",
						cmd), ": No such file or directory\n")), NULL);
	else if (is_path(cmd) && access(cmd, X_OK) == -1)
		return (mini->status = 126, ft_printf_fd(STDERR_FILENO, "minicoquil\
lage: %s: Permission denied\n", cmd), NULL);
	else if (is_path(cmd) && is_dir(cmd))
		return (mini->status = 126, NULL);
	else if (is_path(cmd) && access(cmd, X_OK) == 0)
		return (cmd);
	return (_get_path(mini, cmd));
}
