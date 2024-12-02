/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:29:56 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

bool	is_op(int type)
{
	if (type == OR || type == AND || type == PIPE || type == CMD_SEP
		|| type == EOE)
		return (true);
	return (false);
}

t_double_link_node	*get_next_op(t_mini *mini, t_double_link_node *beg,
		t_double_link_node *end)
{
	int	count_parenthesis;

	count_parenthesis = 0;
	mini->control.token = beg->data;
	if (mini->control.token->type == OPEN_PARENTHESIS)
		count_parenthesis++;
	while ((count_parenthesis || !is_op(mini->control.token->type))
		&& beg->next != end->next)
	{
		beg = beg->next;
		mini->control.token = beg->data;
		if (mini->control.token->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (mini->control.token->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
	}
	return (beg);
}

void	count_token(t_double_link_node *beg, t_double_link_node *end,
		t_token_count *count)
{
	t_token	*token;

	token = beg->data;
	while (!is_op(token->type) && beg && beg != end->next)
	{
		token = beg->data;
		if (token->type == COMMAND)
			count->cmd++;
		else if (token->type == ARG || token->type == OPTION)
			count->args++;
		else if (token->type == HERE_DOC)
			count->heredoc_eof++;
		else if (token->type == REDIRECTION)
		{
			if (token->value[0] == '>')
				count->std_out++;
			else
				count->std_in++;
		}
		beg = beg->next;
	}
}

void	alloc_atom(t_mini *mini, t_token_count count, t_atom *atom)
{
	atom->std_in = wrap_malloc(mini, 
			sizeof(*atom->std_in) * (count.std_in + 1));
	atom->std_in[count.std_in] = NULL;
	atom->std_out = wrap_malloc(mini, 
			sizeof(*atom->std_out) * (count.std_out + 1));
	atom->std_out[count.std_out] = NULL;
	atom->std_order = wrap_malloc(mini,
			 sizeof(char) * (count.std_out
				+ count.std_in + 1));
	atom->std_order[count.std_in + count.std_out] = '\0';
	atom->append = wrap_malloc(mini, 
			sizeof(*atom->append) * (count.std_out));
	atom->args = wrap_malloc(mini, 
			sizeof(*atom->args) * (count.args + count.cmd + 1));
	atom->args[count.args + count.cmd] = NULL;
	atom->heredoc_eof = wrap_malloc(mini,
			 sizeof(*atom->heredoc_eof)
			* (count.heredoc_eof + 1));
	atom->heredoc_eof[count.heredoc_eof] = NULL;
}

int	fill_atom(t_mini *mini, t_ast_node **current_node, t_double_link_node *beg,
		t_double_link_node *end)
{
	t_parser_node	*p_node;
	t_token_count	count;

	count = (t_token_count){};
	p_node = wrap_malloc(mini, 
			sizeof(*p_node));
	*p_node = (t_parser_node){};
	p_node->atom = wrap_malloc(mini, 
			sizeof(*p_node->atom));
	*p_node->atom = (t_atom){};
	(*current_node)->left->data = p_node;
	count_token(beg, end, &count);
	alloc_atom(mini, count, p_node->atom);
	fill_in(p_node->atom, beg, end);
	return (EXIT_SUCCESS);
}
