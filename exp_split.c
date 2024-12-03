/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:34:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

t_expanded	*_init_dosplit(t_mini *mini, char *str, bool *litteral)
{
	t_expanded	*exp;
	int			count;
	t_index		ind;

	exp = wrap_malloc(mini, sizeof(*exp));
	count = _count_split(str, litteral);
	if (!count)
		count = 1;
	exp->value = wrap_malloc(mini, sizeof(*exp->value) * (count + 1));
	exp->litteral = wrap_malloc(mini, sizeof(*exp->litteral) * count);
	exp->value[count] = NULL;
	ind.i = 0;
	ind.j = -1;
	if (!str[ind.i])
	{
		exp->value[++ind.j] = wrap_malloc(mini, sizeof(char));
		exp->litteral[ind.j] = wrap_malloc(mini, sizeof(bool));
		exp->value[ind.j][0] = '\0';
		exp->litteral[ind.j][0] = true;
	}
	return (exp);
}

void	__init(t_mini *mini, t_to_expand *to_expand, t_expanded **expanded,
		t_index *index)
{
	index->i = 0;
	index->j = -1;
	*expanded = _init_dosplit(mini, to_expand->str, to_expand->litteral);
	index->count = 0;
}

t_expanded	*_do_split(t_mini *mini, t_to_expand *t)
{
	t_index		index;
	t_expanded	*expanded;

	__init(mini, t, &expanded, &index);
	while (t->str[index.i])
	{
		index.k = index.i;
		if (t->str[index.i] && (!ft_isspace(t->str[index.i])
				|| t->litteral[index.i]))
		{
			while (t->str[index.i] && (!ft_isspace(t->str[index.i])
					|| t->litteral[index.i]))
				__do(&index);
		}
		else
		{
			while (t->str[index.i] && ft_isspace(t->str[index.i])
				&& !t->litteral[index.i])
				index.i++;
		}
		_assign_value(mini, &expanded, &index, t);
		if (!t->str[index.i])
			break ;
	}
	return (expanded);
}

t_expanded	*_assign_split(t_mini *mini, t_expanded *expanded, int c)
{
	t_expanded	*r;
	t_expanded	*splitted;
	t_to_expand	to_expand;
	t_index		index;

	r = wrap_malloc(mini, sizeof(*expanded));
	r->value = wrap_malloc(mini, sizeof(*r->value) * (c + 1));
	r->litteral = wrap_malloc(mini, sizeof(*r->litteral) * (c));
	r->value[c] = NULL;
	index.i = -1;
	index.j = -1;
	while (expanded->value[++index.i])
	{
		index.k = -1;
		to_expand.litteral = expanded->litteral[index.i];
		to_expand.str = expanded->value[index.i];
		splitted = _do_split(mini, &to_expand);
		while (splitted->value[++index.k])
			__ass_split(r, splitted, &index);
	}
	return (r);
}

t_expanded	*_split_arg(t_mini *mini, t_expanded *expanded)
{
	t_index	index;
	int		count;

	index.i = -1;
	count = 0;
	while (expanded->value[++index.i])
	{
		index.j = _count_split(expanded->value[index.i],
				expanded->litteral[index.i]);
		if (index.j)
			count += index.j;
		else
			count++;
	}
	return (_assign_split(mini, expanded, count));
}
