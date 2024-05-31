/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/31 17:05:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	check_syntax(char *line)
{
	static int	open_double;
	static int	open_single;

	while (*line)
	{
		if (*line == '\'')
		{
			if (open_single)
				open_single = 0;
			else if (!open_double)
				open_single = 1;
		}
		else if (*line == '\"')
		{
			if (open_double)
				open_double = 0;
			else if (!open_single)
				open_double = 1;
		}
		line++;
	} return (!(open_double || open_single));
}

char	*concat_input(t_double_link_list *list)
{
	t_double_link_node	*node;
	t_double_link_node	*temp_node;
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

char	*get_line(void)
{
	char			*prompt;
	char			*line;
	t_control_dll	control;
	char			*final;

	init_control(&control);
	prompt = get_prompt(&control);
	line = init_line(&control, prompt);
	while (!check_syntax(line))
		line = update_node(&control, prompt, line);
	final = concat_input(control.list);
	if (final && *final)
		add_history(final);
	if (!control.list->first_node->next)
		final = ft_strdup(final);
	if (!final)
		return (dl_free_list(control.list), free(prompt), free(line),
			exit(EXIT_FAILURE), NULL);
	dl_free_list(control.list);
	return (free(prompt), final);
}

void populate_tokens(t_double_link_list * list)
{
    t_double_link_node * node;
    t_token * token;
    t_token * previous_token;
    size_t len_token;

    node = list->first_node->next;
    while (node)
    {
        token = node->data;
        previous_token = node->previous->data;
        len_token = ft_strlen(token->value);
        if(ft_strnstr(token->value, "-", len_token) && (previous_token->type == COMMAND || previous_token->type == OPTION))
            token->type = OPTION;
        else if(ft_strnstr(token->value, "--", len_token) && (previous_token->type == COMMAND || previous_token->type == OPTION))
            token->type = OPTION;
        else if(len_token == 1 && token->value[0] == '|')
            token->type = PIPE;
        else if(len_token == 1 && token->value[0] == '(')
            token->type = OPEN_PARENTHESIS;
        else if(len_token == 1 && token->value[0] == ')')
            token->type = CLOSE_PARENTHESIS;
        else if(len_token == 1 && (token->value[0] == '<' || token->value[0] == '>'))
            token->type = REDIRECTION;
        else if(ft_strnstr(">>", token->value, 2))
            token->type = REDIRECTION;
        else if(ft_strnstr("<<" ,token->value, 2))
            token->type = HERE_DOC;
        else if(ft_strnstr(";" ,token->value, 1))
            token->type = CMD_SEP;
        else if (ft_strnstr("&&", token->value, 2))
            token->type = AND;
        else if (ft_strnstr("||", token->value, 2))
            token->type = OR;
        else if(previous_token->type == COMMAND || previous_token->type == OPTION || previous_token->type == REDIRECTION || previous_token->type == HERE_DOC)
            token->type = ARG;
        node = node->next;
    }
}

t_double_link_list	**tokenizer(void)
{
	char				**multiline;
	char				*line;
    t_control_dll control;

	line = get_line();
    if (!line || !*line)
        return (free(line),NULL);
	control.list = create_tokens(line);
	free(line);
    populate_tokens(control.list);
    if (check_error_tokens(&control))
        return (NULL);
	print_list(control.list);
	dl_free_token_list(control.list);
	return (NULL);
}

int	main(void)
{
	t_double_link_list	**tokens_lists;
	int					i;

	// i = 3;
	while (1)
	{
		tokens_lists = tokenizer();
		// i--;
	}
	return (0);
}
