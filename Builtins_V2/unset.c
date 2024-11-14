#include "./builtins.h"


int	msg_error(char *msg_origin)
{
	char	*msg;

	msg = msg_origin;
	while (*msg)
	{
		if (!ft_isalnum(*msg) && *msg != '_')
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(msg_origin, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		msg++;
	}
	return (0);
}

static int	is_present(t_mylist *env, char *variable)
{
	t_mylist	*envc;
	int			i;

	i = 0;
	envc = env;
	while (envc)
	{
		if (!ft_strncmp(variable, envc->var, ft_strlen(variable) + 1))
			return (i);
		envc = envc->next;
		i++;
	}
	return (-1);
}

void	del_var(t_mylist *envc, int position)
{
	int			i;
	int			j;
	t_mylist	*prev;
	t_mylist	*next;

	i = 0;
	j = position - 1;
	next = envc;
	while (i <= position)
	{
		if (position == 0 || i == j)
			prev = next;
		i++;
		if (next->next && i != position)
			next = next->next;
	}
	if (i > 0)
	{
		prev->next = next->next;
		free(next->var);
		free(next->val);
		free(next);
	}
}


/**
 * ft_unset: unset the variable in the environment from the linked list
 * @env: list of environment variables transformed into a linked list t_mylist
 * @variable: the variable to unset
 * @return: 0 if the variable is unset, 1 if the variable is not found
 * 			env is updated
 * To free:
 * 				- no free
 */
int	ft_unset(t_mylist *env, char *variable)
{
	char	**tab;
	int		i;
	int		is_set;
	int		status;
	t_mylist	*envc;

	status = 0;
	if (variable == NULL)
		return (status);
	tab = ft_split(variable, ' ');
	i = 0;
	while (tab[i])
	{
		if (msg_error(tab[i]))
			;
		else
		{
			envc = env;
			is_set = is_present(envc, tab[i]);
			if (is_set > -1)
				del_var(envc, is_set);
		}
		i++;
	}
	return (status);
}

int	mini_unset(char **args, char ***envp)
{
	t_mylist	*envc;
	int			status;
	size_t		lenenv;
	char		**env;

	status = 0;
	env = envp[0];
	while (*(++args))
	{
		envc = ft_env(env);
		if (args)
		{
			status += ft_unset(envc, *(args));
			ft_free_tab(env, ft_tab2len(env));
			env = env_to_tab(envc);
			ft_free_envl(envc);

		}
	}
	*envp = env;
	return (status);
}


// int main(int ac , char **av, char **envp)
// {
// 	t_mylist *envlist;
// 	char 	**envtab;
// 	char  *to_export[] = {"export", "z=Z", "zoz=ZZ", "z_oo=name", NULL};
// 	char  *to_unset[] = {"unset", "zoz", "z_oo", NULL};
// 	int i = 0;

// 	envlist = ft_env(envp);
// 	envtab = env_to_tab(envlist);
// 	mini_export(to_export, &envtab);
// 	mini_env(envtab);
// 	mini_unset(to_unset, &envtab);
// 	mini_env(envtab);
// 	return (0);
// }





// int	main(int ac, char **av, char **env)
// {
// 	t_mylist	*envc;

// 	(void )		ac;
// 	(void )		av;
// 	envc = ft_env(env);
// 	ft_unset(envc, av[1]);
// 	put_envc(envc);
// 	return (0);
// }



// int	is_present(char **env, char *variable)
// {
// 	if (get_env(env, variable))
// 		return (1);
// 	return (0);
// }

// void	remove_var(char **env, char *variable)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	char *to_remove = get_var_env(variable, env);
// 	ft_printf("%s\n", to_remove);
// 	while (ft_strncmp(env[i], to_remove, ft_strlen(to_remove)))
// 		i++;
// 	j = i + 1;
// 	while (env[j])
// 	{
// 		env[i] = env[j];
// 		i++;
// 		j++;
// 	}
// 	env[i] = NULL;
// }

// void	ft_unset(char **env, char *variable)
// {
// 	if (is_present(env, variable))
// 		remove_var(env, variable);
// }

