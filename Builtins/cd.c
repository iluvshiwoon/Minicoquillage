#include "./builtins.h"

char	*put_var_env(char *var, char **env, char *value)
{

	if (!env || !*env)
		return (NULL);
	while (env || *env)
	{
		if (ft_strnstr(*env, var, ft_strlen(var) + 1))
		{
			*env = ft_strdup(value);
			return (*env);
		}
		else
			++env;
	}
	return (NULL);
}

char	*value_new(char *path, char **env)
{
	char *name = ft_strdup("PWD=");
	char *new = ft_strjoin((const char*)name, (const char*)path);
	return (new);
}

int	change_dir(char *oldpwd, char *newpath, char **env)
{
	char	*var;

	if (chdir(newpath))
		return (1);
	var = put_var_env("PWD=", env, value_new(newpath, env));
	return (0);
}

void	ft_cd(char *newpath, char **env)
{
	if (change_dir(getenv("PWD"), newpath, env))
		ft_putstr_fd(CD_ERR, 2);

}

// int	main(int ac, char **av, char **environment)
// {
// 	char **env = ft_env(environment);
// 	char *path = "";
// 	ft_cd(path, env);
// 	put_env(env);
// 	return (0);
// }
