/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:52 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int	check_syntax(char *line)
{
	int	open_double;
	int	open_single;
	int	open_parenthesis;

	open_double = 0;
	open_single = 0;
	open_parenthesis = 0;
	while (*line)
	{
		if (*line == '(' && (!open_single && !open_double))
			++open_parenthesis;
		else if (*line == ')' && (!open_single && !open_double))
			--open_parenthesis;
		if (*line == '\'')
			toggle_quote(&open_double, &open_single, *line);
		else if (*line == '\"')
			toggle_quote(&open_double, &open_single, *line);
		line++;
	}
	if (open_parenthesis < 0)
		open_parenthesis = 0;
	if (open_double || open_single || open_parenthesis)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*concat_input(t_heap_allocated *heap_allocated,
		t_double_link_list *list)
{
	t_double_link_node	*node;
	size_t				i;
	t_string			string;

	i = count_node(list);
	string = (t_string){};
	node = list->first_node;
	if (i == 1)
		string.dst = node->data;
	else if (i-- >= 2)
	{
		string.dst = mini_ft_strjoin(heap_allocated, heap_allocated->input,
				node->data, node->next->data);
		node = node->next->next;
	}
	while (i-- != 1)
	{
		string.temp = mini_ft_strjoin(heap_allocated, heap_allocated->input,
				string.dst, node->data);
		string.dst = string.temp;
		node = node->next;
	}
	return (string.dst);
}

int	check_temp_syntax(t_mini *mini, char *line)
{
	t_control_dll	control_temp;
	int				r_value;

	if (!line || !(*line))
		return (EXIT_FAILURE);
	control_temp.list = create_tokens(mini, line);
	control_temp.complete = 0;
	populate_tokens(&control_temp);
	r_value = check_error_tokens(&control_temp);
	if (r_value == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (r_value == CONTINUE)
		return (CONTINUE);
	return (EXIT_SUCCESS);
}

int	handle_line(t_mini *mini, t_get_line *get_line, t_double_link_list *lines,
		int *r_value)
{
	if (*r_value == EXIT_FAILURE)
	{
		if (get_line->line && *get_line->line)
			add_history(get_line->line);
		return (EXIT_FAILURE);
	}
	get_line->line = update_node(&mini->heap_allocated, lines);
	if (!get_line->line)
		return (EXIT_FAILURE);
	get_line->line = concat_input(&mini->heap_allocated, lines);
	*r_value = check_temp_syntax(mini, get_line->line);
	return (EXIT_SUCCESS);
}

char	*get_line(t_mini *mini)
{
	int					r_value;
	t_get_line			get_line;
	t_double_link_list	*lines;
	t_double_link_node	*node;
	int					i;

	_init_get(mini, &lines, &node, &get_line);
	if (g_signal == SIGINT || !get_line.line)
		return (NULL);
	i = -1;
	while (get_line.line[++i] && ft_isspace(get_line.line[i]))
		;
	if (get_line.line[i] == 0)
		return (NULL);
	r_value = check_temp_syntax(mini, get_line.line);
	get_line.temp = get_line.line;
	if (check_syntax(get_line.temp) == EXIT_FAILURE)
	{
		node->data = mini_ft_strdup(&mini->heap_allocated,
				mini->heap_allocated.input, "\n");
		lines->pf_insert_end(lines, node);
	}
	_check(mini, &get_line, lines, &r_value);
	get_line.line = concat_input(&mini->heap_allocated, lines);
	return (get_line.line);
}
