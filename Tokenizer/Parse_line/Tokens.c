/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:29:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/09 16:28:04 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../Minicoquillage.h"

void	expand_tokens(t_double_link_node *node)
{
	t_control_dll	control;
	t_open_quote	open;
	char			*temp;
	size_t			j;

	init_expand(&open, &control, &j, node);
	while (control.token->value[j])
	{
        if (handle_quote(&control, &open, j) == EXIT_SUCCESS)
			j = j;
        else if (control.token->value[j] == '$' && !open.double_quote && !open.single_quote)
        {
            expand(&j, &control.token->value,
					&temp, &node);
        }
        else if (control.token->value[j] == '"' && open.double_quote)
		{
			open.double_quote = expand_double_quote(&j, &control.token->value,
					&temp, &node);
			control.token->quote = DOUBLE;
		}
        else if (control.token->value[j] == '\'' && open.single_quote)
		{
			open.single_quote = expand_single_quote(&j, &control.token->value,
					&temp, &node);
			control.token->quote = SINGLE;
		}
		++j;
	}
}

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

int	is_sep(char *line, size_t *i, size_t *j, t_control_dll *control)
{
	size_t	k;

	if (ft_sep(line[*i]) && !ft_sep(line[*j]))
		return (1);
	if (ft_sep(line[*j]))
	{
		if (*j && !ft_isspace(line[*j - 1]) && !ft_sep(line[*j - 1]))
		{
			add_token(*i, *j, line, control);
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

t_double_link_list	*create_tokens(char *line)
{
	t_control_dll	control;
	t_open_quote	open;
	size_t			i;
	size_t			j;

	i = init_create_tokens(&open, &control, line, &j);
	while (line[j])
	{
		if (!check_quote(line[j], &open) && (!open.single_quote
				&& !open.double_quote) && (ft_isspace(line[j]) || is_sep(line,
					&i, &j, &control)))
		{
			add_token(i, j, line, &control);
			j = skip_space(line, j);
			skip_space_wrapper(j, &i, line, &open);
		}
		if (line[j])
			++j;
	}
	return (expand_nodes(i, j, &control, line));
}
