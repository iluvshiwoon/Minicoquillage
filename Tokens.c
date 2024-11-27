/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:29:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minicoquillage.h"

int	shenanigans(char *line, size_t *i, size_t *j, size_t *k)
{
	size_t	l;

	l = (*j == *i);
	--(*k);
	if ((line[*i] == '(' || line[*i] == ')' || line[*i] == ';')
		|| (line[*i] != line[*j + l] && ft_sep(line[*j + l])) || !(*k))
	{
		if (*j == *i)
			(*j)++;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	is_sep(char *line, size_t *i, size_t *j, t_mini *mini)
{
	size_t	k;

	if (ft_sep(line[*i]) && !ft_sep(line[*j]))
		return (1);
	if (ft_sep(line[*j]))
	{
		if (*j && !ft_isspace(line[*j - 1]) && !ft_sep(line[*j - 1]))
		{
			add_token(*i, *j, line, mini);
			*i = *j;
		}
		k = 2 + (*j == *i);
		while (ft_sep(line[*j]))
		{
			if (shenanigans(line, i, j, &k) == EXIT_FAILURE)
				break ;
			(*j)++;
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	skip_space_wrapper(size_t j, size_t *i, char *line, t_open_quote *open)
{
	if (ft_isspace(line[j]))
		*i = j + 1;
	else
	{
		*i = j;
		check_quote(line[*i], open);
	}
}

t_double_link_list	*create_tokens(t_mini *mini, char *line)
{
	t_open_quote	open;
	size_t			i;
	size_t			j;

	i = init_create_tokens(&open, mini, line, &j);
	while (line[j])
	{
		if (!check_quote(line[j], &open) && (!open.single_quote
				&& !open.double_quote) && (ft_isspace(line[j]) || is_sep(line,
					&i, &j, mini)))
		{
			add_token(i, j, line, mini);
			j = skip_space(line, j);
			skip_space_wrapper(j, &i, line, &open);
		}
		if (line[j])
			++j;
	}
	return (expand_nodes(i, j, mini, line));
}
