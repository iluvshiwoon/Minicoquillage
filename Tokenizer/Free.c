/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:45:59 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 12:54:16 by kgriset          ###   ########.fr       */
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

void	dl_free_token_list(t_double_link_list *tokens_list)
{
	t_double_link_node	*node;
	t_double_link_node	*node_temp;
	t_token				*token;

	node = tokens_list->first_node;
	while (node)
	{
		token = node->data;
		free(token->value);
		free(node->data);
		node_temp = node;
		node = node->next;
		free(node_temp);
	}
	free(tokens_list);
}
