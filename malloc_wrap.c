/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:57:56 by kgriset          ###   ########.fr       */
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

void	free_heap(t_mini *mini, bool all)
{
	if (!mini)
		return ;
	if (mini->heap_allocated.input)
		dl_free_list(mini->heap_allocated.input);
	if (mini->heap_allocated.tokens)
		dl_free_list(mini->heap_allocated.tokens);
	if (mini->heap_allocated.ast)
		dl_free_list(mini->heap_allocated.ast);
	if (mini->heap_allocated.exec)
		dl_free_list(mini->heap_allocated.exec);
	if (mini->fds)
		free(mini->fds);
	if (all)
		free_all(mini);
}

void	free_all(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->heap_allocated.env)
		dl_free_list(mini->heap_allocated.env);
}

void	*wrap_malloc(t_mini *mini, size_t size)
{
	t_double_link_node	*new_node;

	if (!mini)
		return (NULL);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (close_fds(mini->fds), free_heap(mini, true), exit(EXIT_FAILURE),
			NULL);
	*new_node = (t_double_link_node){};
	new_node->data = malloc(size);
	if (!new_node->data)
		return (close_fds(mini->fds), free(new_node), free_heap(mini, true),
			exit(EXIT_FAILURE), NULL);
	mini->list->pf_insert_end(mini->list, new_node);
	return (new_node->data);
}
