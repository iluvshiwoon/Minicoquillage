/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:10:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 15:21:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

void	toggle_quote(int *open_double, int *open_single, char c)
{
	if (!*open_double && !*open_single && c == '"')
		*open_double += 1;
	else if (!*open_double && !*open_single && c == '\'')
		*open_single += 1;
	else if (*open_double && c == '"')
		*open_double = 0;
	else if (*open_single && c == '\'')
		*open_single = 0;
}

void	init_control(t_mini *mini, t_control_dll *gl_control)
{
	gl_control->list = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.input, sizeof(*mini->control.list));
	gl_control->node = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.input, sizeof(*mini->control.node));
	*gl_control->node = (t_double_link_node){};
	*gl_control->list = (t_double_link_list){};
	init_list(gl_control->list);
}

char	*init_line(t_heap_allocated *heap_allocated, t_double_link_list *lines,
		char *prompt)
{
	char				*line;
	char				*dup_line;
	t_double_link_node	*node;
	int					_stdin;

	_stdin = dup(STDIN_FILENO);
	line = readline(prompt);
	if (g_signal == SIGINT)
		return (dup2(_stdin, STDIN_FILENO), close(_stdin), line);
	if (!line)
		return (_close(_stdin), free_heap(heap_allocated, true), exit(0), NULL);
	node = wrap_malloc(heap_allocated, heap_allocated->input, sizeof(*node));
	dup_line = mini_ft_strdup(heap_allocated, heap_allocated->input, line);
	free(line);
	_close(_stdin);
	node->data = dup_line;
	lines->pf_insert_end(lines, node);
	return (dup_line);
}

char	*update_node(t_heap_allocated *heap_allocated,
		t_double_link_list *lines)
{
	t_double_link_node	*node;
	char				*line;

	node = wrap_malloc(heap_allocated, heap_allocated->input, sizeof(*node));
	*node = (t_double_link_node){};
	line = readline("· ");
	if (!line)
		return (NULL);
	node->data = mini_ft_strjoin(heap_allocated, heap_allocated->input, line,
			"\n");
	lines->pf_insert_end(lines, node);
	return (line);
}
