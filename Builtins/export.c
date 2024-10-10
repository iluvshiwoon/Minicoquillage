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
		if (!ft_strncmp(envc->var, var, ft_strlen(var) + 1))
			return (0);
		envc = envc->next;
	}
	return (1);
}

int	is_formatted(char *var, char *subchar)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	if (has_character(var, '=') < 0 || ft_isdigit(*var))
		return (0);
	while (*var)
	{
		if ( *var == ';' || *var == '|' || *var == '<' || *var == '>' || *var == '&')
			return (0);
		if (ft_isalnum(*var) || *var == '=')
		{
			subchar[1] = subchar[1] + 1;
			var++;
		}
		else
		{
			subchar[1] = subchar[1] + 1;
			subchar[0] = subchar[1];
			var++;
		}
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

int	add_var(t_mylist **env, char *variable, char *subchar)
{
	char	*val;
	char	*var;
	int		separator;
	char	*valc;
	char	*varc;

	separator = has_character(variable, '=');
	varc = NULL;
	var = ft_substr(variable, 0, separator);
	val = ft_substr(variable, separator + 1, ft_strlen(variable) - separator);
	if (val == NULL)
		val = ft_strdup("");
	if (has_character(var, '$') == 0)
		return (1);
	else if (has_character(var, '$') > 0)
		varc = var;
	if (varc)
	{
		var = ft_substr(varc, 0, has_character(varc, '$'));
		free(varc);
	}
	valc = ft_substr(val, 0, has_character(val, '$'));
	free(val);
	addto_env(env, var, valc);
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
		if (!ft_strncmp(envc->var, var, ft_strlen(var) + 1))
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
	varc = NULL;
	var = ft_substr(variable, 0, separator);
	if (has_character(var, '$') == 0)
		return (1);
	else if (has_character(var, '$') > 0)
		varc = var;
	if (varc)
	{
		var = ft_substr(varc, 0, has_character(varc, '$'));
		free(varc);
	}
	val = ft_substr(variable, separator + 1, ft_strlen(variable) -separator);
	if (val == NULL)
		val = ft_strdup("");
	valc = ft_substr(val, 0, has_character(val, '$'));
	free(val);
	updateto_env(env, var, valc);
	return (0);
}

void	ft_export(t_mylist *env, char *variable)
{
	char	**tab;
	char	subchar[2];
	int		is_form;
	int		i;

	tab = ft_split(variable, ' ');
	i = 0;
	while (tab[i])
	{
		subchar[0] = 0;
		subchar[1] = 0;
		is_form = is_formatted(tab[i], subchar);
		if (is_form)
		{
			if (var_missing(&env, tab[i]))
				add_var(&env, tab[i], subchar);
			else
				update_var(&env, tab[i]);
		}
		i++;
	}
}


// int	main(int ac, char **av, char **env)
// {
// 	t_mylist	*envc;

// 	(void )		ac;
// 	(void )		av;
// 	envc = ft_env(env);
// 	ft_export(envc, av[1]);
// 	return (0);
// }

// int	isformatted(char *var, char *subchar)
// {
// 	int i;

// 	i = 0;
// 	if (!var)
// 		return (0);
// 	if (has_character(var, '=') < 0 || ft_atoi(*var))
// 		return (0);
// 	while (*var)
// 	{
// 		if (ft_isalpha(*var) || ft_isdigit(*var) || *var == '=')
// 		{
// 			subchar[1] = subchar[1] + 1;
// 			var++;
// 		}
// 		else
// 		{
// 			subchar[1] = subchar[1] + 1;
// 			subchar[0] = subchar[1];
// 			var++;
// 		}
// 	}
// 	return (1);
// }

// void	add_to_env(char **env, char *variable)
// {
// 	char	**cpy;

// 	cpy = env;
// 	while (*cpy)
// 		cpy++;
// 	*cpy = ft_strdup(variable);
// 	cpy++;
// 	*cpy = NULL;
// }

// void	ft_export(char **env, char *variable)
// {
// 	char	subchar[2];
// 	char	*var;

// 	subchar[0] = 0;
// 	subchar[1] = 0;
// 	if (isformatted(variable, subchar))
// 	{
// 		var = ft_substr(variable, subchar[0], subchar[1] - subchar[0]);
// 		add_to_env(env, var);
// 	}
// }

