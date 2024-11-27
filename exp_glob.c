/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:32:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int	_count_glob(t_heap *heap, char *str, bool *litteral)
{
	int		count;
	t_glob	*globbed;

	globbed = glob(heap, str, litteral);
	count = 0;
	while (globbed)
	{
		count++;
		globbed = globbed->next;
	}
	return (count);
}

void	__init_assign_glob(t_heap *heap, int count, t_index *index,
		char ***r_value)
{
	(*r_value) = wrap_malloc(heap->heap_allocated, heap->list,
			sizeof(*(*r_value)) * (count + 1));
	(*r_value)[count] = NULL;
	index->i = -1;
	index->j = -1;
}

char	**_assign_glob(t_heap *heap, t_expanded *expanded, int count)
{
	t_glob	*globbed;
	char	**r_value;
	t_index	index;

	__init_assign_glob(heap, count, &index, &r_value);
	while (expanded->value[++index.i])
	{
		globbed = glob(heap, expanded->value[index.i],
				expanded->litteral[index.i]);
		if (globbed)
		{
			while (globbed)
			{
				r_value[++index.j] = globbed->file;
				globbed = globbed->next;
			}
		}
		else
		{
			++index.j;
			r_value[index.j] = expanded->value[index.i];
		}
	}
	return (r_value);
}

char	**_glob_args(t_heap *heap, t_expanded *expanded)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	expanded = _split_arg(heap, expanded);
	while (expanded->value[++i])
	{
		j = _count_glob(heap, expanded->value[i], expanded->litteral[i]);
		if (j)
			count += j;
		else
			count++;
	}
	return (_assign_glob(heap, expanded, count));
}
