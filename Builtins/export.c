#include "./builtins.h"

int	has_character(char *var, char c)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = var;
	while (*cpy)
	{
		if (*cpy == c)
			return (i);
		cpy++;
		i++;
	}
	return (-1);
}

int	error_message(char *tab)
{
	int	i;

	i = 0;
	ft_putstr_fd("export: `", 2);
	while (tab[i] != '\0' && tab[i] != '\n')
	{
		ft_putchar_fd(tab[i], 2);
		i++;
	}
	if (has_character(tab, '=') == -1)
		ft_putchar_fd('=', 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	var_missing(t_mylist **env, char *str)
{
	t_mylist	*envc;
	char		*var;
	int			separator;

	separator = has_character(str, '=');
	var = ft_substr(str, 0, separator);

	envc = *env;
	while (envc)
	{
		if (!ft_strncmp(envc->var, var, ft_strlen(var)))
			return (0);
		envc = envc->next;
	}
	return (1);
}

void	addto_env(t_mylist **env, char *var, char *val)
{
	t_mylist	*envc;
	t_mylist	*new;

	new = malloc(sizeof(t_mylist));
	if (!new)
		return ;
	new->var = var;
	new->val = val;
	new->next = NULL;
	envc = *env;
	while (envc->next)
		envc = envc->next;
	envc->next = new;
}

int	add_var(t_mylist **env, char *variable)
{
	char	*val;
	char	*var;
	int		separator;
	int 	end_var;

	separator = has_character(variable, '=');
	if (separator < 0)
	{
		end_var = ft_strlen(variable) - 1;
		if (variable[end_var] == '\n')
			var = ft_substr(variable, 0, end_var);
		else
			var = variable;
		val = ft_strdup("");
	}
	else
	{
		var = ft_substr(variable, 0, separator);
		val = ft_substr(variable, separator + 1, ft_strlen(variable) - separator - 2);
	}
	if (!ft_strncmp(val, "=", 1))
		val = ft_strdup("");
	addto_env(env, var, val);
	return (0);
}

void	updateto_env(t_mylist **env, char *var, char *val)
{
	t_mylist	*envc;
	char		*old_env_val;

	envc = *env;
	while (envc)
	{
		old_env_val = envc->val;
		if (!ft_strncmp(envc->var, var, ft_strlen(var)))
		{
			envc->val = val;
			free(old_env_val);
			return ;
		}
		envc = envc->next;
	}
}

int	update_var(t_mylist **env, char *variable)
{
	char		*var;
	char		*val;
	char		*valc;
	char		*varc;
	int			separator;

	separator = has_character(variable, '=');
	{
		var = ft_substr(variable, 0, separator);
		val = ft_substr(variable, separator + 1, ft_strlen(variable) - separator - 2);
	}
	if (!ft_strncmp(val, "=", 1))
		val = ft_strdup("");
	updateto_env(env, var, val);
	return (0);
}

int error_case(char **tab, int i, char *firstchar)
{
	if (tab[i][0] == '=')
	{
		error_message(tab[i]);
		return (1);
	}
	else if (!ft_isalpha((*firstchar)))
	{
		error_message(tab[i]);
		return (1);
	}
	return (0);
}

/**
 * ft_export - export a variable from the env list
 * @env: list of environment variables transformed into a linked list t_mylist
 * @variable: the variable to export
 * @return: 0 if the variable is exported, 1 if the variable is not exported,
 * 			env is updated
 */
int	ft_export(t_mylist *env, char *variable)
{
	char	**tab;
	int		is_form;
	int		i;
	char	*firstchar;
	int		status;

	status = 0;
	tab = ft_split(variable, ' ');
	i = 0;
	while (tab[i])
	{
		firstchar = ft_substr(tab[i], 0, 1);
		if (error_case(tab, i, firstchar))
			status += 1;
		else
		{
			if (var_missing(&env, tab[i]))
				add_var(&env, tab[i]);
			else
				update_var(&env, tab[i]);
		}
		i++;
		free(firstchar);
	}
	return (status);
}
