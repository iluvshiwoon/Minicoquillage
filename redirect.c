/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:39:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:43:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__redirect(t_mini *mini, t_atom *atom)
{
	if (atom->heredoc)
		atom->in_fd = m_open(mini, atom->file_heredoc, O_RDONLY, 0);
	if (atom->in_fd)
		m_dup2(mini, atom->in_fd, STDIN_FILENO);
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
	__redirect(mini, atom);
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
