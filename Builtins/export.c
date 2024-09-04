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

int	is_formatted(char *var, char *subchar)
{
	int i;

	i = 0;
	if (!var)
		return (0);
	if (has_character(var, '=') < 0 || ft_isdigit(*var))
		return (0);
	while (*var)
	{
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
	val = ft_substr(variable, separator, ft_strlen(variable) -separator);
	if (has_character(var, '$') == 0)
		return (1);
	else if(has_character(var, '$') > 0)
		varc = var;
	if(varc)
	{
		var = ft_substr(varc, 0, has_character(varc, '$'));
		free(varc);
	}
	valc = ft_substr(val, 0, has_character(val, '$'));
	free(val);
	addto_env(env, var, valc);
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
			add_var(&env, tab[i], subchar);
		i++;
	}
}



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

