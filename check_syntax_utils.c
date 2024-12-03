/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:10:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:59:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

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
	gl_control->list = wrap_malloc(mini, sizeof(*mini->control.list));
	gl_control->node = wrap_malloc(mini, sizeof(*mini->control.node));
	*gl_control->node = (t_double_link_node){};
	*gl_control->list = (t_double_link_list){};
	init_list(gl_control->list);
}

char	*init_line(t_double_link_list *lines, char *prompt, t_mini *mini)
{
	char				*line;
	char				*dup_line;
	t_double_link_node	*node;
	int					_stdin;

	_stdin = m_dup(mini, STDIN_FILENO);
	line = readline(prompt);
	if (g_signal == SIGINT)
		return (m_dup2(mini, _stdin, STDIN_FILENO), close(_stdin), line);
	if (!line)
		return (close_fds(mini->fds), free_heap(mini, true), exit(mini->status),
			NULL);
	node = wrap_malloc(mini, sizeof(*node));
	dup_line = mini_ft_strdup(mini, line);
	free(line);
	node->data = dup_line;
	lines->pf_insert_end(lines, node);
	return (dup_line);
}

char	*update_node(t_mini *mini, t_double_link_list *lines)
{
	t_double_link_node	*node;
	char				*line;
	char				*dup_line;

	node = wrap_malloc(mini, sizeof(*node));
	*node = (t_double_link_node){};
	line = readline("· ");
	if (!line)
		return (NULL);
	dup_line = mini_ft_strdup(mini, line);
	free(line);
	node->data = mini_ft_strjoin(mini, dup_line, "\n");
	lines->pf_insert_end(lines, node);
	return (dup_line);
}
