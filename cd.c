/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:56:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 15:37:03 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*wrap_getcwd(t_mini *mini)
{
	char	*r_value;
	char	*temp;

	r_value = getcwd(NULL, 0);
	if (!r_value)
		return (ft_printf_fd(STDERR_FILENO, "error retrieving current di\
rectory: getcwd: cannot access parent directories: %s\n",
				strerror(errno)), NULL);
	temp = r_value;
	r_value = mini_ft_strdup(mini, r_value);
	free(temp);
	return (r_value);
}

void	f_export(t_mini *mini, char *var, char *value)
{
	char	**f_args;

	f_args = wrap_malloc(mini, sizeof(*f_args) * 3);
	f_args[0] = "prout";
	f_args[1] = mini_ft_strjoin(mini, var, value);
	f_args[2] = NULL;
	mini_export(mini, f_args);
}

char	*get_home(t_mini *mini)
{
	char	*home;

	home = _getenv(mini, "HOME");
	if (!home)
	{
		home = _getenv(mini, "USER");
		if (!home)
		{
			home = wrap_getcwd(mini);
			if (!home)
				return (NULL);
		}
		else
			home = mini_ft_strjoin(mini, "/home/", home);
	}
	return (home);
}

int	_cd(t_mini *mini, char *path)
{
	int		i;
	char	*cur_dir;

	if (!path)
		return (1);
	i = chdir(path);
	if (i != 0)
		return (ft_printf_fd(STDERR_FILENO, "minicoquillage: cd: %s: %s\n",
				path, strerror(errno)), 1);
	cur_dir = _getenv(mini, "OLDPWD");
	if (cur_dir)
	{
		cur_dir = _getenv(mini, "PWD");
		if (cur_dir)
			f_export(mini, "OLDPWD=", cur_dir);
	}
	cur_dir = _getenv(mini, "PWD");
	if (cur_dir)
	{
		cur_dir = wrap_getcwd(mini);
		if (cur_dir)
			f_export(mini, "PWD=", mini_ft_strdup(mini, cur_dir));
	}
	return (0);
}

int	mini_cd(t_mini *mini, char **args)
{
	int		i;
	char	*path;
	char	*home;

	i = 0;
	path = args[1];
	while (args[++i])
		;
	if (i > 2)
		return (ft_printf_fd(STDERR_FILENO,
				"minicoquillage: cd: too many arguments\n"), 1);
	if (args[1] == NULL)
		path = get_home(mini);
	else if (args[1][0] == '~')
	{
		home = get_home(mini);
		if (home)
			path = mini_ft_strjoin(mini, home, path + 1);
	}
	else if (ft_strncmp(args[1], "-", _max_len(ft_strlen(args[1]), 1)) == 0)
		__print_cd(mini, &path);
	return (_cd(mini, path));
}
