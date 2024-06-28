#include "./exec.h"
#include <unistd.h>

int	pss_ok(char *path)
{
	if (access((const char *)path, F_OK | X_OK) != -1)
		return (1);
	else
		return (0);
}

char	*pss_permission(char **envs_path, char *cmd)
{
	int		i;
	char	**c;
	char	*full_path;
	char	*cmd_path;

	c = ft_split(cmd, ' ');
	i = 1;
	cmd_path = ft_strdup("");
	while (!pss_ok(cmd_path) && envs_path[i])
	{
		full_path = ft_strjoin(envs_path[i], "/");
		cmd_path = ft_strjoin(full_path, c[0]);
		free(full_path);
		i++;
	}
	if (!pss_ok(cmd_path))
		return (NULL);
	ft_free_tab(c, ft_strlen2(c));
	return (cmd_path);
}

char	*get_path(char **env)
{
	if (!env || !*env)
		return (NULL);
	while (env || *env)
	{
		if (ft_strnstr(*env, "PATH=/", 6))
			return (*env);
		else
			++env;
	}
	return (NULL);
}

void	exec_(char *cmd, char **envs_path, char **arg_s, char *cmd_path)
{
	char	*sx;
	char	**splitstr;
	int		lensplit;

	splitstr = ft_split(cmd, '/');
	lensplit = ft_strlen2(splitstr);
	sx = splitstr[lensplit - 1];
	cmd_path = pss_permission(envs_path, sx);
	arg_s[0] = ft_split(sx, ' ')[0];
	if (execve(cmd_path, arg_s, NULL) == -1)
	{
		perror("Error: command not found\n");
		exit(127);
	}
}

void	execution(char *cmd_, char **envs_path)
{
	char	*cmd_path;
	char	**arg_s;
	char	**init_path;

	cmd_path = NULL;
	arg_s = ft_split(cmd_, ' ');
	init_path = ft_split(arg_s[0], '/');
	if (ft_strlen2(init_path) < 2)
	{
		cmd_path = pss_permission(envs_path, cmd_);
		if (execve(cmd_path, arg_s, NULL) == -1)
		{
			perror("Error: command not found\n");
			exit(127);
		}
	}
	else
		exec_(cmd_, envs_path, arg_s, cmd_path);
	ft_free_tab(arg_s, ft_strlen2(arg_s));
	ft_free_tab(init_path, ft_strlen2(init_path));
}
