/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:36:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 15:34:12 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

bool	_is_valid_exp(char c)
{
	const char	*valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLM\
NOPQRSTUVWXYZ0123456789_?";

	if (ft_strchr(valid_chars, c))
		return (true);
	return (false);
}

char	*__init_count_exp(int *k, int i, int *count, char **var)
{
	*k = i;
	*count = 0;
	*var = NULL;
	return (NULL);
}

int	_count_exp(t_mini *mini, char *str, int *i, t_to_expand _expand)
{
	int		k;
	int		count;
	char	*r_value;
	char	*var;

	r_value = __init_count_exp(&k, *i, &count, &var);
	while (str[++k] && _is_valid_exp(str[k]) == true)
	{
		var = wrap_malloc(mini, sizeof(*var) * (k - *i + 1));
		ft_strlcpy(var, str + *i + 1, (k - *i + 1));
		r_value = _getenv(mini, var);
		if (!ft_strncmp("?", var, _max_len(ft_strlen(var), 1)))
			break ;
	}
	if (r_value)
		++k;
	if (k - *i == 1)
		if (!((str[k] == '"' && !_expand.open.double_quote) || str[k] == '\''))
			++count;
	if (r_value)
		count += ft_strlen(r_value);
	if (var)
		*i += ft_strlen(var);
	return (count);
}

void	__assign_exp(t_mini *mini, char **r_value)
{
	(*r_value) = wrap_malloc(mini, sizeof(char) * 2);
	(*r_value)[0] = '$';
	(*r_value)[1] = '\0';
}

char	*_assign_exp(t_mini *mini, char *str, int *i, t_to_expand _expand)
{
	int		k;
	char	*r_value;
	char	*var;

	init_ass(&k, *i, &r_value, &var);
	while (str[++k] && _is_valid_exp(str[k]) == true)
	{
		var = wrap_malloc(mini, sizeof(*var) * (k - *i + 1));
		ft_strlcpy(var, str + *i + 1, (k - *i + 1));
		r_value = _getenv(mini, var);
		if (!ft_strncmp("?", var, _max_len(ft_strlen(var), 1)))
			break ;
	}
	if (r_value)
		++k;
	if (k - *i == 1)
	{
		if (!((str[k] == '"' && !_expand.open.double_quote) || str[k] == '\''))
			__assign_exp(mini, &r_value);
	}
	if (var)
		*i += ft_strlen(var);
	return (r_value);
}
