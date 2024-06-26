/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:26:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 15:27:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

size_t	count_node(t_double_link_list *list)
{
	t_double_link_node	*node;
	size_t				i;

	node = list->first_node;
	i = 0;
	while (node)
	{
		node = node->next;
		++i;
	}
	if (!i)
		return (dl_free_list(list), exit(EXIT_FAILURE), i);
	return (i);
}
