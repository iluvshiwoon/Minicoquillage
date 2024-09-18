/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:02:52 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/18 17:24:02 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

int	check_syntax(char *line)
{
	static int	open_double;
	static int	open_single;
	static int	open_parenthesis;

	while (*line)
	{
		if (*line == '(' && (!open_single && !open_double))
			++open_parenthesis;
		else if (*line == ')' && (!open_single && !open_double))
			--open_parenthesis;
		if (*line == '\'')
			toggle_quote(&open_single, &open_double);
		else if (*line == '\"')
			toggle_quote(&open_double, &open_single);
		line++;
	}
	if (open_parenthesis < 0)
		open_parenthesis = 0;
	if (open_double || open_single)
		return (EXIT_FAILURE);
	else if (open_parenthesis)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*concat_input(t_double_link_list *list)
{
	t_double_link_node	*node;
	// t_double_link_node	*temp_node;
	size_t				i;
	t_string			string;

	i = count_node(list);
	string = (t_string){};
	node = list->first_node;
	if (i == 1)
		string.dst = node->data;
	else if (i-- >= 2)
	{
		string.dst = wrapper_strjoin_concat((char *)node->data,
				(char *)node->next->data, list, &string);
		node = node->next->next;
	}
	while (i-- != 1)
	{
		string.temp = wrapper_strjoin_concat(string.dst, (char *)node->data,
				list, &string);
		free(string.dst);
		string.dst = string.temp;
		node = node->next;
	}
	return (string.dst);
}

int	check_temp_syntax(char *line)
{
	t_control_dll	control_temp;
	int				r_value;

	if (!line || !(*line))
		return (EXIT_FAILURE);
	control_temp.list = create_tokens(line);
	control_temp.complete = 0;
	populate_tokens(&control_temp);
	r_value = check_error_tokens(&control_temp);
	if (r_value == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (r_value == CONTINUE)
		return (CONTINUE);
	return (dl_free_token_list(control_temp.list), EXIT_SUCCESS);
}

int	handle_line(t_get_line *get_line, t_control_dll *control, int *r_value)
{
	if (*r_value == EXIT_FAILURE)
	{
		if (get_line->line && *get_line->line)
			add_history(get_line->line);
		return (dl_free_list(control->list), free(get_line->prompt),
			EXIT_FAILURE);
	}
	get_line->temp = update_node(control, get_line->prompt, get_line->line);
	get_line->line = concat_input(control->list);
	*r_value = check_temp_syntax(get_line->line);
	return (EXIT_SUCCESS);
}

char	*get_line(void)
{
	t_control_dll	control;
	int				r_value;
	t_get_line		get_line;

	init_control(&control);
	get_line.prompt = get_prompt(&control);
	get_line.line = init_line(&control, get_line.prompt);
	get_line.temp = get_line.line;
	r_value = check_temp_syntax(get_line.line);
	while (check_syntax(get_line.temp) == EXIT_FAILURE
		|| r_value == EXIT_FAILURE || r_value == CONTINUE)
	{
		if (handle_line(&get_line, &control, &r_value) == EXIT_FAILURE)
			return (NULL);
	}
	get_line.line = concat_input(control.list);
	if (get_line.line && *get_line.line)
		add_history(get_line.line);
	if (!control.list->first_node->next)
		get_line.line = ft_strdup(get_line.line);
	if (!get_line.line)
		return (dl_free_list(control.list), free(get_line.prompt),
			free(get_line.line), exit(EXIT_FAILURE), NULL);
	return (dl_free_list(control.list), free(get_line.prompt), get_line.line);
}
