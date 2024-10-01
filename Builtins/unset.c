#include "./builtins.h"

static int	is_present(t_mylist *env, char *variable)
{
	t_mylist	*envc;
	int			i;

	i = 0;
	envc = env;
	while (envc)
	{
		if (!ft_strncmp(variable, envc->var, ft_strlen(envc->var)))
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
		if (position == 0 || i == j )
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

void	ft_unset(t_mylist *env, char *variable)
{
	char	**tab;
	int		i;
	int		is_set;

	tab = ft_split(variable, ' ');
	i = 0;
	while (tab[i])
	{
		is_set = is_present(env, tab[i]);
		if (is_set > -1)
			del_var(env, is_set);
		i++;
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	t_mylist	*envc;

// 	(void )		ac;
// 	(void )		av;
// 	envc = ft_env(env);

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

