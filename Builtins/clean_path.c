#include "./builtins.h"



static int	is_absolute(char *vpath)
{
	int		i;
	char	*double_dot;
	char	*tilt;
	char	**split_path;

	split_path = ft_split(vpath, '/');
	while (split_path[i])
	{
		if (ft_strncmp(split_path[i], "..", 2) == 0)
			return (1);
		if (ft_strncmp(split_path[i], "~", 1) == 0)
			return (1);
		i++;
	}
	//ft_free(split_path);
	return (0);

}

to_absolute(char *vpath)
{
	char	*to_path;
	char	*home;
	char	*tmp;
	char	**split_path;
	int		i;

	i = 0;
	home = get_var_env("HOME");
	split_path = ft_split(vpath, '/');
	while (split_path[i])
	{
		if (ft_strncmp(split_path[i], "~", 1) == 0)
		{
			tmp = ft_strjoin(home, split_path[i] + 1);
			free(split_path[i]);
			split_path[i] = tmp;
		}
		i++;
	}
	to_path = ft_strjoin("/", split_path[0]);
	i = 1;
	while (split_path[i])
	{
		tmp = ft_strjoin(to_path, "/");
		free(to_path);
		to_path = ft_strjoin(tmp, split_path[i]);
		free(tmp);
		i++;
	}
	return (to_path);
}

char	*get_var_env(char *vpath)
{
	int		type_path;
	char	*to_path;

	type_path = is_absolute(vpath);
	if (type_path == 0)
	{
		return (vpath);
	}
	else
	{
		to_path = to_absolute(vpath);
		return (to_path);
	}
}
