/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/19 01:42:00 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
#include "stdlib.h"

void	print_error(char *error, t_token *token)
{
	if (token)
		printf(error, token->value);
	else if (!token)
		printf(error, NULL);
}

int	check_error1(t_control_dll *control, t_token *next)
{
	char	*error;

	error = "minicoquillage: syntax error near unexpected token `%s'\n";
	if (control->token->type >= REDIRECTION && control->token->type <= HERE_DOC
		&& next->type >= REDIRECTION && next->type <= HERE_DOC)
		return (print_error(error, next), EXIT_FAILURE);
	else if ((control->token->type == REDIRECTION || control->token->type == HERE_DOC)&& next->type != R_FILE)
		return (print_error(error, next), EXIT_FAILURE);
	else if (control->token->type >= CMD_SEP && control->token->type <= OR
		&& next->type >= CMD_SEP && next->type <= OR)
		return (print_error(error, next), EXIT_FAILURE);
	else if (control->token->type == OPEN_PARENTHESIS
		&& next->type >= CLOSE_PARENTHESIS && next->type <= OR)
		return (print_error(error, next), EXIT_FAILURE);
	else if (control->token->type == CLOSE_PARENTHESIS
		&& !(next->type >= CLOSE_PARENTHESIS && next->type <= HERE_DOC))
		return (print_error(error, next), EXIT_FAILURE);
    else if (next->type == OPEN_PARENTHESIS &&\
            !((control->token->type >= CMD_SEP && control->token->type <= OR)||control->token->type == OPEN_PARENTHESIS))
		return (print_error(error, next), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_error(t_control_dll *control, t_token *next)
{
	char	*error;
	char	*newline;

	error = "minicoquillage: syntax error near unexpected token `%s'\n";
	newline = "minicoquillage: syntax error near unexpected token `newline'\n";
	if (!next || !control->token)
	{
		if (!next && control->token->type >= PIPE && control->token->type <= OR)
			return (CONTINUE);
		else if (!next && control->token->type >= REDIRECTION
			&& control->token->type <= HERE_DOC)
			return (print_error(newline, NULL), EXIT_FAILURE);
		else if (!control->token && next->type >= CMD_SEP && next->type <= OR)
			return (print_error(error, next), EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (control->token->type >= COMMAND && control->token->type <= HERE_DOC
		&& control->token->type != CLOSE_PARENTHESIS
		&& next->type == control->token->type)
		return (print_error(error, next), EXIT_FAILURE);
	return (check_error1(control, next));
}

int	check_parenthesis(t_control_dll *control)
{
	int		parenthesis;
	char	*error;

	error = "minicoquillage: syntax error near unexpected token `%s'\n";
	parenthesis = 0;
	control->node = control->list->first_node;
	while (control->node && control->complete)
	{
		control->token = control->node->data;
		if (control->token->type == OPEN_PARENTHESIS)
			++parenthesis;
		else if (control->token->type == CLOSE_PARENTHESIS)
			--parenthesis;
		control->node = control->node->next;
	}
	if (parenthesis < 0)
		return (print_error(error, control->token), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_error_tokens(t_control_dll *control)
{
	t_token	*next;
	int		r_value;

	control->node = control->list->first_node;
	control->token = NULL;
    next = NULL;
	if (check_error(control, control->list->first_node->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (control->node)
	{
		control->token = control->node->data;
		if (control->node->next)
			next = control->node->next->data;
		else
			next = NULL;
		r_value = check_error(control, next);
		if (r_value == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (r_value == CONTINUE)
			return (CONTINUE);
		control->node = control->node->next;
	}
	if (check_error(control, next) == CONTINUE)
		return (CONTINUE);
	return (check_parenthesis(control));
}
