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
    prev = NULL;
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

int	mini_unset(char **args, char **env)
{
	t_mylist	*envc;
	int			status;

	status = 0;
	while (!status || *args)
	{
		envc = ft_env(env);
		status += ft_unset(envc, *(++args));
		ft_free_tab(env, ft_tab2len(env));
		env = env_to_tab(envc);
		ft_free_envl(envc);
	}
	return (status);
}
