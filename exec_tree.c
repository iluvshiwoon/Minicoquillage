/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/01 17:24:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_exec_pipe(t_mini *mini, t_parser_node **p_node,
		t_ast_node **first_node, t_exec *exec)
{
	t_ast_node	*left;

	left = (*first_node)->left;
	(*p_node) = (*first_node)->data;
	if ((*p_node)->ops && (*p_node)->ops == PIPE && !exec->skip)
	{
		exec->skip = 1;
		mini->status = _pipeline(mini, (*first_node), *exec);
		while ((*p_node)->ops && (*p_node)->ops == PIPE)
		{
			(*first_node) = (*first_node)->right;
			(*p_node) = (*first_node)->data;
		}
	}
	(*p_node) = left->data;
	if (!exec->skip)
		redirect(mini, exec, *first_node);
}

void	_exec_exec(t_mini *mini, t_parser_node **p_node,
		t_ast_node **first_node, t_exec *exec)
{
	char	**globbed;

	if (is_op((*p_node)->ops) && !exec->skip)
	{
		_exec_tree(mini, (*first_node)->left, (*exec).fds);
		(*p_node) = (*first_node)->data;
		if ((*p_node)->atom && (*p_node)->atom->in_fd)
			_close((*p_node)->atom->in_fd);
		if ((*p_node)->atom && (*p_node)->atom->out_fd)
			_close((*p_node)->atom->out_fd);
		(*p_node) = (*first_node)->left->data;
	}
	else if (!exec->skip)
	{
		globbed = _glob_args(&mini->heap, _expand(mini, (*p_node)->atom->args));
		if (check_builtin(&mini->heap, globbed[0]))
			mini->status = _call_builtin(mini, globbed, *exec);
		else
			mini->status = _exec_node(mini, globbed);
		if ((*p_node)->atom && (*p_node)->atom->in_fd)
			_close((*p_node)->atom->in_fd);
		if ((*p_node)->atom && (*p_node)->atom->out_fd)
			_close((*p_node)->atom->out_fd);
	}
	(*p_node) = (*first_node)->data;
}

void	_exec_tree(t_mini *mini, t_ast_node *first_node,
		t_double_link_list *fds)
{
	t_parser_node	*p_node;
	t_exec			exec;

	exec.fds = fds;
	__dup(mini, &exec);
	exec.skip = 0;
	while (first_node && first_node->left)
	{
		_exec_pipe(mini, &p_node, &first_node, &exec);
		_exec_exec(mini, &p_node, &first_node, &exec);
		if (p_node->ops)
		{
			if ((p_node->ops == AND && mini->status) || (p_node->ops == OR
					&& !mini->status))
				exec.skip = 1;
			else if (p_node->ops && p_node->ops != PIPE)
				exec.skip = 0;
		}
		_reset_fd(exec);
		first_node = first_node->right;
	}
}
