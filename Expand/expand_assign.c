/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:03:13 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 00:14:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_change_quote(bool *litteral, int *open)
{
	*litteral = false;
	*open = 0;
}

void	_init_assign(bool *litteral, t_open_quote *open, t_index *index)
{
	*litteral = false;
	open->double_quote = 0;
	open->single_quote = 0;
	index->i = -1;
	index->j = 0;
}

void	__assign(t_to_expand *_expand, char *r_value, t_index *index,
		bool litteral)
{
	if (r_value)
	{
		while (r_value[++index->k])
		{
			_expand->litteral[index->j] = litteral;
			_expand->str[index->j++] = r_value[index->k];
		}
	}
}

void	__assign_copy(t_to_expand *_expand, t_index *index, bool litteral,
		char *to_expand)
{
	_expand->litteral[index->j] = litteral;
	_expand->str[index->j++] = to_expand[index->i];
}

void	_assign(t_mini *mini, char *to_expand, t_to_expand *_expand)
{
	t_index	index;
	bool	litteral;
	char	*r_value;

	_init_assign(&litteral, &_expand->open, &index);
	while (to_expand[++index.i])
	{
		if (_handle_quote(to_expand[index.i], &_expand->open) == EXIT_SUCCESS)
			litteral = true;
		else if (to_expand[index.i] == '$' && !_expand->open.single_quote)
		{
			index.k = -1;
			r_value = _assign_exp(mini, to_expand, &index.i, *_expand);
			__assign(_expand, r_value, &index, litteral);
		}
		else if (to_expand[index.i] == '"' && _expand->open.double_quote)
			_change_quote(&litteral, &_expand->open.double_quote);
		else if (to_expand[index.i] == '\'' && _expand->open.single_quote)
			_change_quote(&litteral, &_expand->open.single_quote);
		else
			__assign_copy(_expand, &index, litteral, to_expand);
		if (!to_expand[index.i])
			break ;
	}
}
