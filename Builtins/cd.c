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

int	go_home(t_mylist *env, t_mylist *oldpath, t_mylist *currentpath)
{
	t_mylist	*home;
	t_mylist	*oldpwd;
	t_mylist	*pwd;

	home = get_var(env, "HOME");
	pwd = get_var(env, "PWD");
	oldpwd = get_var(env, "OLDPWD");
	if(home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home->val) != 0)
	{
		printf("cd: %d (%s)\n", errno, strerror(errno));
		return (1);
	}
	else
	{
		put_var(env, "OLDPWD", pwd->val);
		put_var(env, "PWD", home->val);
		return (0);
	}
}

int	change_dir(t_mylist *env_origin, t_mylist *oldpath, t_mylist *currentpath, char *newpath)
{
	t_mylist	*pwd;
	t_mylist	*env;

	pwd = currentpath;
	env = env_origin;
	if (chdir((const char *) newpath) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newpath, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	else
	{
		put_var(env, "OLDPWD", pwd->val);
		put_var(env, "PWD", newpath);
		return (0);
	}
}

int	ft_cd_abs(char *newpath, t_mylist *env)
{
	t_mylist	*currentpath;
	t_mylist	*oldpath;

	currentpath = get_var(env, "PWD");
	oldpath = get_var(env, "OLDPWD");
	if (!newpath || !ft_strncmp(newpath, "", 1))
		return go_home(env, oldpath, currentpath);
	else
		return change_dir(env, oldpath, currentpath, newpath);
}

int	is_absolute_path(char *path)
{
	int	i;

	i = 0;
	if (path[i])
	{
		if (path[i] == '~' && path[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}

int ft_cd_rel(char *relative_path, t_mylist *env)
{
	t_mylist	*currentpath;
	t_mylist	*oldpath;
	t_mylist	*username;
	char		*goto_path;

	username = get_var(env, "USERNAME");
	currentpath = get_var(env, "PWD");
	oldpath = get_var(env, "OLDPWD");
	if(relative_path[0] == '~')
	{
		goto_path = ft_strjoin(get_var(env, "HOME")->val, relative_path + 1);
	}
	else
	{
		goto_path = relative_path;;
	}
	return ft_cd_abs(goto_path, env);
}


int	ft_cd(char *new_path, t_mylist *env)
{
	t_mylist	*currentpath;
	char		*path;

	currentpath = get_var(env, "PWD");
	if (!new_path)
		return ft_cd_abs(NULL, env);
	else
	{
		path = my_vpath(new_path, currentpath);
		printf("path: %s\n", path);
		if (is_absolute_path(new_path))
			return ft_cd_rel(new_path, env);
		else
			return ft_cd_abs(new_path, env);
	}
}


int main(int ac , char **av, char **env)
{
	t_mylist	*env_list;
	char		*new_path;

	env_list = ft_env(env);
	if (ac == 1)
		ft_cd(NULL, env_list);
	else
	{
		new_path = av[1];
		ft_cd(new_path, env_list);
	}
	return (0);
}
