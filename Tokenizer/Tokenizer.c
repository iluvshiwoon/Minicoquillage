/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 11:29:55 by bsunda           ###   ########.fr       */
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

int check_temp_syntax(char * line)
{
	t_control_dll control_temp;
	int r_value;

	if (!line || !(*line))
		return (0);
	control_temp.list = create_tokens(line);
	control_temp.complete = 0;
	populate_tokens(&control_temp);
	r_value = check_error_tokens(&control_temp);
	if(r_value== 1)
		return (1);
	else if (r_value == 2)
		return (2);
	return (dl_free_token_list(control_temp.list),0);
}

char	*get_line(void)
{
	char			*prompt;
	char			*line;
	t_control_dll	control;
	char			*temp;
	int r_value;

	init_control(&control);
	prompt = get_prompt(&control);
	line = init_line(&control, prompt);
	temp = line;
	r_value = check_temp_syntax(line);
	while (!check_syntax(temp) || r_value)
	{
		if (r_value == 1)
		{
			if (line && *line)
					add_history(line);
			return(dl_free_list(control.list),free(prompt),NULL);
		}
		temp = update_node(&control, prompt, line);
		line = concat_input(control.list);
		r_value = check_temp_syntax(line);
	}
	line = concat_input(control.list);
	if (line && *line)
		add_history(line);
	if (!control.list->first_node->next)
		line = ft_strdup(line);
	if (!line)
		return (dl_free_list(control.list), free(prompt), free(line),
			exit(EXIT_FAILURE), NULL);
	dl_free_list(control.list);
	return (free(prompt), line);
}

void populate_first_token(t_control_dll * control)
{
	t_token * previous_token;
	size_t len_token;

	control->token = control->list->first_node->data;
	len_token = ft_strlen(control->token->value);
	if (control->token->quote != NONE)
		return;
	if(len_token == 1 && control->token->value[0] == '|')
		control->token->type = PIPE;
	else if(len_token == 1 && control->token->value[0] == '(')
		control->token->type = OPEN_PARENTHESIS;
	else if(len_token == 1 && control->token->value[0] == ')')
		control->token->type = CLOSE_PARENTHESIS;
	else if(len_token == 1 && (control->token->value[0] == '<' || control->token->value[0] == '>'))
		control->token->type = REDIRECTION;
	else if(!ft_strncmp(control->token->value, ">>", len_token))
		control->token->type = REDIRECTION;
	else if(!ft_strncmp(control->token->value, "<<", len_token))
		control->token->type = HERE_DOC;
	else if(!ft_strncmp(control->token->value, ";", len_token))
		control->token->type = CMD_SEP;
	else if (!ft_strncmp(control->token->value, "&&", len_token))
		control->token->type = AND;
	else if (!ft_strncmp(control->token->value, "||", len_token))
		control->token->type = OR;
	else if (!ft_strncmp(control->token->value, "&|", len_token))
		control->token->type = AND;
	else if (!ft_strncmp(control->token->value, "|&", len_token))
		control->token->type = AND;
}

// int is_option(char * string)
// {
//     size_t i;
//     int option;
//
//     i = 0;
//     option = 1;
//     while (string[i])
//     {
//         if (i > 1 && string[i] == '-')
//         {
//             option = 0;
//             break;
//         }
//         ++i;
//     }
//     return (option);
// }

void populate_tokens(t_control_dll * control)
{
	t_double_link_node * node;
	t_token * previous_token;
	size_t len_token;

	node = control->list->first_node->next;
	populate_first_token(control);
	while (node)
	{
		control->token = node->data;
		previous_token = node->previous->data;
		len_token = ft_strlen(control->token->value);
		if(ft_strnstr(control->token->value, "-", len_token) && (previous_token->type == COMMAND || previous_token->type == OPTION || previous_token->type == ARG))
			control->token->type = OPTION;
		else if(ft_strnstr(control->token->value, "--", len_token) && (previous_token->type == COMMAND || previous_token->type == OPTION))
			control->token->type = OPTION;
		else if(control->token->quote == NONE &&len_token == 1 && control->token->value[0] == '|')
			control->token->type = PIPE;
		else if(control->token->quote == NONE &&len_token == 1 && control->token->value[0] == '(')
			control->token->type = OPEN_PARENTHESIS;
		else if(control->token->quote == NONE &&len_token == 1 && control->token->value[0] == ')')
			control->token->type = CLOSE_PARENTHESIS;
		else if(control->token->quote == NONE &&len_token == 1 && (control->token->value[0] == '<' || control->token->value[0] == '>'))
			control->token->type = REDIRECTION;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, ">>", len_token + (len_token < 2)))
			control->token->type = REDIRECTION;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, "<<", len_token + (len_token < 2)))
			control->token->type = HERE_DOC;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, ";" , len_token + (len_token < 2)))
			control->token->type = CMD_SEP;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, "&&", len_token + (len_token < 2)))
			control->token->type = AND;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, "&|", len_token + (len_token < 2)))
			control->token->type = AND;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, "|&", len_token + (len_token < 2)))
			control->token->type = AND;
		else if(control->token->quote == NONE && !ft_strncmp(control->token->value, "||", len_token + (len_token < 2)))
			control->token->type = OR;
		else if(previous_token->type == COMMAND || previous_token->type == OPTION || previous_token->type == REDIRECTION || previous_token->type == HERE_DOC || previous_token->type == ARG)
			control->token->type = ARG;
		node = node->next;
	}
}

t_double_link_list	**tokenizer(t_double_link_list **list)
{
	char				**multiline;
	char				*line;
	t_control_dll control;

	line = get_line();
	if (!line || !*line)
		return (free(line),NULL);
	control.list = create_tokens(line);
	control.complete = 1;
	free(line);
	populate_tokens(&control);
	print_list(control.list);
	if (check_error_tokens(&control))
		return (NULL);
	// dl_free_token_list(control.list);
	list = &(control.list);
	return list;
}

t_double_link_list	**debug(char * line)
{
	char				**multiline;
	t_control_dll control;

	control.list = create_tokens(line);
	control.complete = 1;
	populate_tokens(&control);
	if (check_error_tokens(&control))
		return (dl_free_token_list(control.list),NULL);
	print_csv(control.list);
	return (dl_free_token_list(control.list),NULL);
}

int	main(int argc, char ** argv, char **env)
{
	char				**envc;
	t_double_link_list	**tokens_lists;

	envc = ft_env(env);
	if (argc == 2)
	{
		tokens_lists = debug(argv[1]);
		return (0);
	}
	while (1)
	{
		tokens_lists = tokenizer(tokens_lists);
		
	}
	return (0);
}
