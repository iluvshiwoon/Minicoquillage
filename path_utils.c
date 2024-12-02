/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:39:13 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:16:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

bool	is_dir(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
		return (ft_printf_fd(STDERR_FILENO, "minicoquillage: \
%s: Is a directory\n", cmd), 1);
	return (0);
}

bool	is_path(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			return (true);
	return (false);
}

bool	check_builtin(t_mini *mini, char *cmd)
{
	char	**split;
	char	*builtin;
	int		i;

	i = -1;
	builtin = "echo,cd,pwd,export,unset,env,exit";
	if (!cmd)
		return (false);
	split = mini_ft_split(mini, builtin, ',');
	while (split[++i])
		if (ft_strncmp(cmd, split[i], _max_len(ft_strlen(cmd),
					ft_strlen(split[i]))) == 0)
			return (true);
	return (false);
}
