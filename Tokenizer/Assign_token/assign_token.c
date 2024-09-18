/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:00:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/18 17:23:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

void	populate_first_token(t_control_dll *control)
{
	// t_token	*previous_token;
	size_t	len_token;

	control->token = control->list->first_node->data;
	len_token = ft_strlen(control->token->value);
	if (control->token->quote != NONE)
		return ;
	if (len_token == 1 && control->token->value[0] == '|')
		control->token->type = PIPE;
	else if (len_token == 1 && control->token->value[0] == '(')
		control->token->type = OPEN_PARENTHESIS;
	else if (len_token == 1 && control->token->value[0] == ')')
		control->token->type = CLOSE_PARENTHESIS;
	else if (len_token == 1 && (control->token->value[0] == '<'
			|| control->token->value[0] == '>'))
		control->token->type = REDIRECTION;
	else if (!ft_strncmp(control->token->value, ">>", len_token))
		control->token->type = REDIRECTION;
	else
		populate_first_token1(control, len_token);
}

void	populate_tokens3(t_control_dll *control, t_token *previous_token,
		size_t len_token, int *cmd)
{
	if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			"||", len_token + (len_token < 2)))
		add_type(control, OR, cmd);
	else if (*cmd && (previous_token->type == COMMAND
			|| previous_token->type == OPTION || previous_token->type == ARG
			|| previous_token->type == R_FILE))
		control->token->type = ARG;
	else if (previous_token->type == REDIRECTION
		|| previous_token->type == HERE_DOC)
		control->token->type = R_FILE;
	if (control->token->type == COMMAND)
		*cmd = 1;
}

void	populate_tokens2(t_control_dll *control, t_token *previous_token,
		size_t len_token, int *cmd)
{
	if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			"<<", len_token + (len_token < 2)))
		control->token->type = HERE_DOC;
	else if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			";", len_token + (len_token < 2)))
		add_type(control, CMD_SEP, cmd);
	else if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			"&&", len_token + (len_token < 2)))
		add_type(control, AND, cmd);
	else if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			"&|", len_token + (len_token < 2)))
		add_type(control, AND, cmd);
	else if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			"|&", len_token + (len_token < 2)))
		add_type(control, AND, cmd);
	else
		populate_tokens3(control, previous_token, len_token, cmd);
}

void	populate_tokens1(t_control_dll *control, t_token *previous_token,
		size_t len_token, int *cmd)
{
	if ((previous_token->type == COMMAND || previous_token->type == OPTION
			|| previous_token->type == R_FILE)
		&& is_option(control->token->value) == EXIT_SUCCESS)
		control->token->type = OPTION;
	else if (control->token->quote == NONE && len_token == 1
		&& control->token->value[0] == '|')
		add_type(control, PIPE, cmd);
	else if (control->token->quote == NONE && len_token == 1
		&& control->token->value[0] == '(')
		add_type(control, OPEN_PARENTHESIS, cmd);
	else if (control->token->quote == NONE && len_token == 1
		&& control->token->value[0] == ')')
		add_type(control, CLOSE_PARENTHESIS, cmd);
	else if (control->token->quote == NONE && len_token == 1
		&& (control->token->value[0] == '<' || control->token->value[0] == '>'))
		control->token->type = REDIRECTION;
	else if (control->token->quote == NONE && !ft_strncmp(control->token->value,
			">>", len_token + (len_token < 2)))
		control->token->type = REDIRECTION;
	else
		populate_tokens2(control, previous_token, len_token, cmd);
}

void	populate_tokens(t_control_dll *control)
{
	t_double_link_node	*node;
	t_token				*previous_token;
	size_t				len_token;
	int					cmd;

	node = control->list->first_node->next;
	cmd = 0;
	populate_first_token(control);
	if (node)
	{
		previous_token = node->previous->data;
		if (previous_token->type == COMMAND)
			cmd = 1;
	}
	while (node)
	{
		control->token = node->data;
		previous_token = node->previous->data;
		len_token = ft_strlen(control->token->value);
		populate_tokens1(control, previous_token, len_token, &cmd);
		node = node->next;
	}
}
