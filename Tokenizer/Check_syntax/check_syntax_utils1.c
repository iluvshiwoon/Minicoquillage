/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:26:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 20:17:39 by kgriset          ###   ########.fr       */
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
	return (i);
}

void	_init_get(t_mini *mini, t_double_link_list **lines,
		t_double_link_node **node, t_get_line *get_line)
{
	*node = wrap_malloc(&mini->heap_allocated, mini->heap_allocated.input,
			sizeof(**node));
	*lines = wrap_malloc(&mini->heap_allocated, mini->heap_allocated.input,
			sizeof(**lines));
	**lines = (t_double_link_list){};
	init_list(*lines);
	get_line->prompt = get_prompt(mini,&mini->heap_allocated);
	get_line->line = init_line(&mini->heap_allocated, *lines, get_line->prompt);
}

void	_check(t_mini *mini, t_get_line *get_line, t_double_link_list *lines,
		int *r_value)
{
	while (check_syntax(get_line->temp) == EXIT_FAILURE
		|| *r_value == EXIT_FAILURE || *r_value == CONTINUE)
	{
		if (handle_line(mini, get_line, lines, r_value) == EXIT_FAILURE)
			break ;
		get_line->temp = concat_input(&mini->heap_allocated, lines);
	}
}
