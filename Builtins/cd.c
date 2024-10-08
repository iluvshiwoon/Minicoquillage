#include "./builtins.h"


t_mylist	*put_var(t_mylist *env_origin, char *var, char *value)
{
	t_mylist	*env;

	env = env_origin;
	while (env)
	{
		if (!ft_strncmp(env->var, var, ft_strlen(var)))
		{
			env->val = ft_strdup(value);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

t_mylist	*get_var(t_mylist *env, char *var)
{
	t_mylist	*currentpath;

	currentpath = env;
	while (env)
	{
		if (!ft_strncmp(env->var, var, ft_strlen(var)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	go_home(t_mylist *env, t_mylist *oldpath, t_mylist *currentpath)
{
	t_mylist	*home;
	t_mylist	*oldpwd;
	t_mylist	*pwd;

	home = get_var(env, "HOME");
	pwd = get_var(env, "PWD");
	oldpwd = get_var(env, "OLDPWD");
	if (chdir(home->val) != 0)
		printf("cd: %d (%s)\n", errno, strerror(errno));
	else
	{
		put_var(env, "OLDPWD", pwd->val);
		put_var(env, "PWD", home->val);
	}
}

void	change_dir(t_mylist *env_origin, t_mylist *oldpath, t_mylist *currentpath, char *newpath)
{
	t_mylist	*pwd;
	t_mylist	*env;

	pwd = currentpath;
	env = env_origin;
	if (chdir((const char *) newpath) != 0)
	{
		// printf("cd: %d (%s)\n", errno, strerror(errno));
		perror("cd: chemin incorrect\n");
	}
	else
	{
		put_var(env, "OLDPWD", pwd->val);
		put_var(env, "PWD", newpath);
	}
}

void	ft_cd(char *newpath, t_mylist *env)
{
	t_mylist	*currentpath;
	t_mylist	*oldpath;

	currentpath = get_var(env, "PWD");
	oldpath = get_var(env, "OLDPWD");
	if (!newpath)
		go_home(env, oldpath, currentpath);
	else
		change_dir(env, oldpath, currentpath, newpath);
}


// int main(int ac, char **av, char **env)
// {
// 	t_mylist	*envc;
// 	char		*path;

// 	path = "/home/bsunda/Documents/projet_1/Minicoquillage/Builtins/test";
// 	// path = "/homes/bsunst";
// 	// path = NULL;
// 	envc = ft_env(env);
// 	ft_cd(path, envc);
// 	// ft_putstr_fd(path, 1);
// 	// put_envc(envc);
// 	return (0);
// }



// char	*put_var_env(char *var, char **env, char *value)
// {

// 	if (!env || !*env)
// 		return (NULL);
// 	while (env || *env)
// 	{
// 		if (ft_strnstr(*env, var, ft_strlen(var) + 1))
// 		{
// 			*env = ft_strdup(value);
// 			return (*env);
// 		}
// 		else
// 			++env;
// 	}
// 	return (NULL);
// }

// char	*value_new(char *path, char **env)
// {
// 	char *name = ft_strdup("PWD=");
// 	char *new = ft_strjoin((const char*)name, (const char*)path);
// 	return (new);
// }

// void	change_dir(char *oldpwd, char *newpath, char **env)
// {
// 	char	*var;

// 	if (chdir(newpath) != 0)
// 		printf("%s\n", "cd error");
// 	var = put_var_env("PWD=", env, value_new(newpath, env));
// }

// void	ft_cd(char *newpath, char **env)
// {
// 	if (change_dir(getenv("PWD"), newpath, env))
// 		ft_putstr_fd(CD_ERR, 2);

// }

// int	main(int ac, char **av, char **environment)
// {
// 	char **env = ft_env(environment);
// 	char *path = "/home/bsunda/Documents/projet_1/Minicoquillage/Builtins/test";
// 	change_dir("", path, env);
// 	// ft_cd(path, env);
// 	put_env(env);
// 	return (0);
// }



