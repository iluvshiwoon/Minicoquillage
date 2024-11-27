/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

t_double_link_list	*init_alloc(t_double_link_list **list)
{
	*list = malloc(sizeof(**list));
	if (!list)
		return (NULL);
	**list = (t_double_link_list){};
	init_list(*list);
	return (*list);
}

void	free_heap(t_heap_allocated *heap_allocated, bool all)
{
	if (!heap_allocated)
		return ;
	if (heap_allocated->tokens)
	{
		dl_free_list(heap_allocated->tokens);
		heap_allocated->tokens = NULL;
	}
	if (heap_allocated->ast)
	{
		dl_free_list(heap_allocated->ast);
		heap_allocated->ast = NULL;
	}
	if (heap_allocated->input)
	{
		dl_free_list(heap_allocated->input);
		heap_allocated->input = NULL;
	}
	if (heap_allocated->exec)
	{
		dl_free_list(heap_allocated->exec);
		heap_allocated->exec = NULL;
	}
	if (all)
		free_env(heap_allocated);
}

void	free_env(t_heap_allocated *heap_allocated)
{
	if (!heap_allocated)
		return ;
	if (heap_allocated->env)
	{
		dl_free_list(heap_allocated->env);
		heap_allocated->env = NULL;
	}
}

void	*wrap_malloc(t_heap_allocated *heap_allocated, t_double_link_list *list,
		size_t size)
{
	t_double_link_node	*new_node;

	if (!list || !heap_allocated)
		return (free_heap(heap_allocated, true), exit(EXIT_FAILURE), NULL);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (free_heap(heap_allocated, true), exit(EXIT_FAILURE), NULL);
	*new_node = (t_double_link_node){};
	new_node->data = malloc(size);
	if (!new_node->data)
		return (free(new_node), free_heap(heap_allocated, true),
			exit(EXIT_FAILURE), NULL);
	list->pf_insert_end(list, new_node);
	return (new_node->data);
}
