/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:59:54 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 15:54:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_init_check_var(int *i, int *r_value)
{
	*i = -1;
	*r_value = 0;
}

int	_check_var(char *var, bool print)
{
	int	i;
	int	r_value;

	_init_check_var(&i, &r_value);
	while (var[++i])
	{
		if (var[i] == '=')
			break ;
		if (i == 0 && ft_isdigit(var[i]))
			r_value = 1;
		else if (!ft_isalnum(var[i]) && var[i] != '_')
			r_value = 1;
	}
	if (var[i] == '\0')
	{
		if (r_value == 0 && i)
			print = false;
		r_value = 1;
	}
	else if (var[i] == '=' && i == 0)
		r_value = 1;
	if (r_value && print)
		return (ft_printf_fd(STDERR_FILENO, "minicoquillage: export: `%s'\
: not a valid identifier\n", var), 2);
	return (r_value);
}

size_t	_count_export(t_mini *mini, char **args, char ***new_env)
{
	int		i;
	int		j;
	size_t	count;

	i = -1;
	j = 0;
	count = 0;
	while (mini->envp[++i])
		;
	while (args[++j])
		if (_check_var(args[j], false) == 0 && _search_var(mini, args[j]))
			count++;
	if (count != 0)
	{
		count += i;
		*new_env = wrap_malloc(mini, sizeof(**new_env) * (count + 1));
		(*new_env)[count] = NULL;
	}
	return (count);
}

void	__export_init(int *i, int *r_value, size_t *count, char ***new_env)
{
	*i = 0;
	*r_value = 0;
	*count = 0;
	*new_env = NULL;
}

int	mini_export(t_mini *mini, char **args)
{
	int		i;
	int		r_value;
	size_t	count;
	char	**new_env;

	mini->list = mini->heap_allocated.env;
	__export_init(&i, &r_value, &count, &new_env);
	while (args[++i])
		if (_check_var(args[i], true) == 2)
			r_value = 1;
	count = _count_export(mini, args, &new_env);
	if (count)
	{
		i = -1;
		while ((mini->envp)[++i])
			new_env[i] = mini_ft_strdup(mini, (mini->envp)[i]);
		count = 0;
		while (args[++count])
			if (_check_var(args[count], false) == 0 && _search_var(mini,
					args[count]))
				new_env[i++] = mini_ft_strdup(mini, args[count]);
		mini->envp = new_env;
	}
	return (r_value);
}
