/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:32:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 04:22:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__init_count(int *i, int *count, t_open_quote *open)
{
	*i = -1;
	*count = 0;
	open->double_quote = 0;
	open->single_quote = 0;
}

int	_count(t_mini *mini, char *str)
{
	int				i;
	int				count;
	t_open_quote	open;
	t_to_expand		_expand;

	__init_count(&i, &count, &open);
	while (str[++i])
	{
		if (_handle_quote(str[i], &open) == EXIT_SUCCESS)
			;
		else if (str[i] == '$' && !open.single_quote)
		{
			mod_expand(&_expand, mini->status, open);
			count += _count_exp(mini, str, &i, _expand);
		}
		else if (str[i] == '"' && open.double_quote)
			open.double_quote = 0;
		else if (str[i] == '\'' && open.single_quote)
			open.single_quote = 0;
		else
			++count;
		if (!str[i])
			break ;
	}
	return (count);
}

void	__assign_expand0(t_mini *mini, t_expanded *expanded, t_index *index)
{
	expanded->litteral[++index->j] = wrap_malloc(mini, sizeof(bool));
	expanded->value[index->j] = wrap_malloc(mini, sizeof(char));
	expanded->value[index->j][0] = '\0';
	expanded->litteral[index->j][0] = true;
}

void	__assign_expand1(t_mini *mini, t_expanded *expanded, t_index *index)
{
	expanded->litteral[++index->j] = wrap_malloc(mini, sizeof(bool)
			* (index->count));
	expanded->value[index->j] = wrap_malloc(mini, sizeof(char) * (index->count
				+ 1));
	expanded->value[index->j][index->count] = '\0';
}

t_expanded	*_expand(t_mini *mini, char **to_expand)
{
	t_expanded	*expanded;
	t_to_expand	_expand;
	t_index		index;

	expanded = wrap_malloc(mini, sizeof(*expanded));
	_init_expand(mini, to_expand, expanded);
	index.i = -1;
	index.j = -1;
	while (to_expand[++index.i])
	{
		index.count = _count(mini, to_expand[index.i]);
		if (!index.count && _is_empty_quote(mini, to_expand[index.i]))
			__assign_expand0(mini, expanded, &index);
		else if (index.count)
		{
			__assign_expand1(mini, expanded, &index);
			_expand.str = expanded->value[index.j];
			_expand.litteral = expanded->litteral[index.j];
			_expand.status = mini->status;
			_assign(mini, to_expand[index.i], &_expand);
		}
	}
	return (expanded);
}
