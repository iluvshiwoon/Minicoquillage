#include "./../exec.h"
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

// char	*get_path(char **env)
// {
// 	if (!env || !*env)
// 		return (NULL);
// 	while (env || *env)
// 	{
// 		if (ft_strnstr(*env, "PATH=/", 6))
// 			return (*env);
// 		else
// 			++env;
// 	}
// 	return (NULL);
// }

char	*get_path(t_mylist *env)
{
	t_mylist	*envc;

	envc = env;
	while (envc)
	{
		if (!ft_strncmp(envc->var, "PATH", 5))
			return (envc->val);
		envc = envc->next;
	}
	return (NULL);
}

char	*ft_sx_path(char *cmd, t_mylist *env_var)
{
	char	*sx_cmd;
	char	*cmd_clean;
	char	**split_cmd;
	int		lensplit;
	char	**envp;

	split_cmd = ft_split(cmd, '/');
	lensplit = ft_strlen2(split_cmd);
	sx_cmd = split_cmd[lensplit - 1];
	cmd_clean = ft_split(sx_cmd, ' ')[0];
	envp = ft_split(get_path(env_var), ':');
	return (pss_permission(envp, sx_cmd));
	//  TODO:manage free & garbage collector
}



// int	main(int ac, char **av, char **env)
// {
// 	char	*cmd;
// 	char	**env_copy;
// 	char	*cmd_path;

// 	cmd = "usr/bin/cat";
// 	env_copy = ft_env(env);
// 	cmd_path = ft_sx_path(cmd, env_copy);
// 	ft_printf("%s\n", cmd_path);
// }
