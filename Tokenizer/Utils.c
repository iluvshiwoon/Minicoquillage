/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/29 17:42:46 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	print_list(t_double_link_list *tokens_lists)
{
	size_t				i;
	t_double_link_node	*node;

	i = 0;
	node = tokens_lists->first_node;
	while (node)
	{
		printf("%s$\n", (char *)node->data);
		node = node->next;
	}
}

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
