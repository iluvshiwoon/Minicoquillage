/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:35:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	fill_redir(t_token *token, t_atom *atom, t_double_link_node *beg,
		t_token_count *count)
{
	if (token->value[0] == '>')
	{
		if (token->value[1] == '>')
			atom->append[count->std_out] = true;
		else
			atom->append[count->std_out] = false;
		token = beg->next->data;
		atom->std_order[count->std_out + count->std_in] = 'o';
		atom->std_out[count->std_out++] = token->value;
	}
	else
	{
		atom->heredoc = false;
		token = beg->next->data;
		atom->std_order[count->std_out + count->std_in] = 'i';
		atom->std_in[count->std_in++] = token->value;
	}
}

void	fill_in(t_atom *atom, t_double_link_node *beg, t_double_link_node *end)
{
	t_token			*token;
	t_token_count	count;

	count = (t_token_count){};
	token = beg->data;
	while (!is_op(token->type) && beg && beg != end->next)
	{
		token = beg->data;
		if (token->type == COMMAND)
		{
			atom->cmd = token->value;
			atom->args[count.args++] = token->value;
		}
		else if (token->type == ARG || token->type == OPTION)
			atom->args[count.args++] = token->value;
		else if (token->type == HERE_DOC)
		{
			atom->heredoc = true;
			token = beg->next->data;
			atom->heredoc_eof[count.heredoc_eof++] = token->value;
		}
		else if (token->type == REDIRECTION)
			fill_redir(token, atom, beg, &count);
		beg = beg->next;
	}
}

void	_compute_skip(t_double_link_node *beg, t_mini *mini)
{
	int	count;

	count = 1;
	mini->control.node = beg;
	while (count)
	{
		mini->control.node = mini->control.node->next;
		if (!mini->control.node)
			break ;
		mini->control.token = mini->control.node->data;
		if (mini->control.token->type == OPEN_PARENTHESIS)
			count++;
		else if (mini->control.token->type == CLOSE_PARENTHESIS)
			count--;
	}
}

void	_alloc_atom(t_mini *mini, t_ast_node **current_node)
{
	(*current_node)->left = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.ast, sizeof(*(*current_node)->left));
	*(*current_node)->left = (t_ast_node){};
	(*current_node)->left->previous = *current_node;
}

int	compute_atom(t_mini *mini, t_double_link_node *beg, t_double_link_node *end,
		t_ast_node **current_node)
{
	int	exit_status;

	_alloc_atom(mini, current_node);
	exit_status = EXIT_SUCCESS;
	mini->control.token = beg->data;
	if (mini->control.token->type == OPEN_PARENTHESIS)
	{
		_compute_skip(beg, mini);
		compute_expr(mini, beg->next, mini->control.node->previous,
			(*current_node)->left);
		(*current_node)->right = wrap_malloc(&mini->heap_allocated,
				mini->heap_allocated.ast, sizeof(*(*current_node)->right));
		*(*current_node)->right = (t_ast_node){};
		(*current_node)->right->previous = (*current_node);
		return (exit_status);
	}
	fill_atom(mini, current_node, beg, end);
	mini->control.token = end->data;
	if (!is_op(mini->control.token->type))
		return (exit_status);
	(*current_node)->right = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.ast, sizeof(*(*current_node)->right));
	*(*current_node)->right = (t_ast_node){};
	(*current_node)->right->previous = (*current_node);
	return (exit_status);
}
