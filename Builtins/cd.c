#include "./builtins.h"


char	*get_var_env(char *var, char **env)
{
	if (!env || !*env)
		return (NULL);
	while (env || *env)
	{
		if (ft_strnstr(*env, var, ft_strlen(var) + 1))
			return (*env);
		else
			++env;
	}
	return (NULL);
}

void	value_old(char *oldpath, char **env)
{
	char *name = ft_strdup("PWD=");
	char *new = ft_strjoin((const char*)name, (const char*)oldpath);
	ft_printf("%s\n", new);
	char *envir = get_working_dir(env, "OLDPWD=");
	envir = ft_strdup(new);
}
void	value_new(char *newpath, char **env)
{
	char *name = ft_strdup("PWD=");
	char *new = ft_strjoin((const char*)name, (const char*)newpath);
	ft_printf("%s\n", new);
	char *envir = get_working_dir("PWD=", env);
	envir = ft_strdup(new);
}

int	change_dir(char *oldpwd, char *newpath, char **env)
{
	char	**cpy_env;

	cpy_env = (env);
	if(chdir(newpath))
		return (1);
	ft_printf("%s\n", getenv("PWD"));
	return (0);
}

void	ft_cd(char *newpath, char **env)
{
	if (change_dir(getenv("PWD"), newpath, env))
		ft_putstr_fd(CD_ERR, 2);

}

int	main(int ac, char **av, char **env)
{
	char *path = "/home/bsunda/Documents/projet_1/Minicoquillage";

	value_new(path, env);
	return (0);
}
