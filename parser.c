/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:19:31 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	skip_through(t_mini *mini, t_parser_node *p_node,
		t_double_link_node *next_op)
{
	t_token				*token;
	t_token_count		count;
	t_double_link_node	*og_next_op;

	count = (t_token_count){};
	token = NULL;
	og_next_op = next_op;
	if (!next_op)
		return ;
	while (next_op->previous)
	{
		token = next_op->previous->data;
		if (token->type == CLOSE_PARENTHESIS)
			break ;
		next_op = next_op->previous;
	}
	if (token && token->type != CLOSE_PARENTHESIS)
		return ;
	p_node->atom = malloc(sizeof(*p_node->atom));
	*p_node->atom = (t_atom){};
	count_token(next_op, og_next_op, &count);
	alloc_atom(mini, count, p_node->atom);
	fill_in(p_node->atom, next_op, og_next_op);
}

void	_skip_skip(int *count, t_double_link_node **i, t_token **token)
{
	(*count)++;
	while ((*count))
	{
		*i = (*i)->next;
		if (!(*i))
			break ;
		*token = (*i)->data;
		if ((*token)->type == OPEN_PARENTHESIS)
			(*count)++;
		else if ((*token)->type == CLOSE_PARENTHESIS)
			(*count)--;
	}
}

void	skip_through_parenthesis(t_mini *mini, t_parser_node *p_node,
		t_double_link_node *beg, t_double_link_node *next_op)
{
	t_double_link_node	*i;
	t_token_count		t_count;
	t_token				*token;
	int					count;

	i = beg;
	count = 0;
	t_count = (t_token_count){};
	token = i->data;
	if (token->type == OPEN_PARENTHESIS)
	{
		_skip_skip(&count, &i, &token);
		if (i && i->next && i->next != next_op)
		{
			p_node->atom = wrap_malloc(&mini->heap_allocated,
					mini->heap_allocated.ast, sizeof(*p_node->atom));
			*p_node->atom = (t_atom){};
			count_token(i->next, next_op, &t_count);
			alloc_atom(mini, t_count, p_node->atom);
			fill_in(p_node->atom, i->next, next_op);
		}
	}
}

void	compute_expr(t_mini *mini, t_double_link_node *beg,
		t_double_link_node *end, t_ast_node *current_node)
{
	t_double_link_node	*next_op;
	t_parser_node		*p_node;

	while (1)
	{
		p_node = wrap_malloc(&mini->heap_allocated, mini->heap_allocated.ast,
				sizeof(*p_node));
		*p_node = (t_parser_node){};
		next_op = get_next_op(mini, beg, end);
		current_node->data = p_node;
		skip_through_parenthesis(mini, p_node, beg, next_op);
		if (next_op == end)
		{
			p_node->ops = EOE;
			compute_atom(mini, beg, end, &current_node);
			break ;
		}
		mini->control.token = next_op->data;
		p_node->ops = mini->control.token->type;
		compute_atom(mini, beg, next_op, &current_node);
		current_node = current_node->right;
		beg = next_op->next;
	}
}

t_ast	*parser(t_mini *mini)
{
	t_double_link_node	*beg;
	t_double_link_node	*end;
	t_ast				*ast;

	ast = wrap_malloc(&mini->heap_allocated, mini->heap_allocated.ast,
			sizeof(*ast));
	*ast = (t_ast){};
	ast->first_node = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.ast, sizeof(*ast->first_node));
	*ast->first_node = (t_ast_node){};
	beg = mini->control.list->first_node;
	end = mini->control.list->last_node;
	compute_expr(mini, beg, end, ast->first_node);
	return (ast);
}
