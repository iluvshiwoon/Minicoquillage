/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:39:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__redirect(t_atom *atom)
{
	if (atom->heredoc)
	{
		_close(atom->in_fd);
		atom->in_fd = open(atom->file_heredoc, O_RDONLY);
	}
	if (atom->in_fd)
		dup2(atom->in_fd, STDIN_FILENO);
}

void	_redirect(t_mini *mini, t_atom *atom, t_exec *exec)
{
	int			i;
	t_expanded	*exp_stdin;
	t_expanded	*exp_stdout;

	i = -1;
	exec->i = -1;
	exec->j = -1;
	exp_stdout = _expand(mini, atom->std_out);
	exp_stdin = _expand(mini, atom->std_in);
	while (atom->std_order[++i] && !(exec->skip))
	{
		if (atom->std_order[i] == 'o' && !(exec->skip))
		{
			++(exec->i);
			_stdout(mini, exp_stdout, atom, exec);
		}
		else if (atom->std_order[i] == 'i' && !(exec->skip))
		{
			++(exec->j);
			_stdin(mini, exp_stdin, atom, exec);
		}
	}
	__redirect(atom);
}

void	redirect(t_mini *mini, t_exec *exec, t_ast_node *first_node)
{
	t_parser_node	*p_node;

	p_node = first_node->left->data;
	if (is_op(p_node->ops))
	{
		p_node = first_node->data;
		if (p_node->atom)
			_redirect(mini, p_node->atom, exec);
	}
	else if (p_node->atom)
		_redirect(mini, p_node->atom, exec);
}
