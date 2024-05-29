/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:45:59 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/29 16:19:49 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	dl_free_list(t_double_link_list *tokens_list)
{
	t_double_link_node	*node;
	t_double_link_node	*node_temp;

	node = tokens_list->first_node;
	while (node)
	{
		free(node->data);
		node_temp = node;
		node = node->next;
		free(node_temp);
	}
	free(tokens_list);
}

void	free_all(char **multiline, t_double_link_list **tokens_list,
		char ***tokens)
{
	size_t	i;

	i = 0;
	if (multiline)
		free_split(multiline);
	if (tokens_list)
	{
		while (tokens_list[i])
			dl_free_list(tokens_list[i++]);
		free(tokens_list);
	}
	if (tokens)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
}
