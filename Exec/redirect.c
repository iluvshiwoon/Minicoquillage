/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:39:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 15:41:17 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_redirect(t_mini *mini, int *skip, t_atom *atom, int og_stdout)
{
	int			i;
	int			j;
	int			k;
	t_expanded	*exp_stdin;
	t_expanded	*exp_stdout;

	i = -1;
	j = -1;
	k = -1;
	exp_stdout = _expand(mini, atom->std_out);
	exp_stdin = _expand(mini, atom->std_in);
	while (atom->std_order[++i] && !(*skip))
	{
		if (atom->std_order[i] == 'o' && !(*skip))
			_stdout(&mini->heap, skip, &(mini->status), exp_stdout, ++j, atom,
				og_stdout);
		else if (atom->std_order[i] == 'i' && !(*skip))
			_stdin(&mini->heap, skip, &(mini->status), exp_stdin, ++k, atom,
				og_stdout);
	}
	if (atom->heredoc)
	{
		_close(atom->in_fd);
		atom->in_fd = open(atom->file_heredoc, O_RDONLY);
	}
	if (atom->in_fd)
		dup2(atom->in_fd, STDIN_FILENO);
}

void	redirect(t_mini *mini, t_exec *exec, t_ast_node *first_node)
{
	t_parser_node	*p_node;

	p_node = first_node->left->data;
	if (is_op(p_node->ops))
	{
		p_node = first_node->data;
		if (p_node->atom)
			_redirect(mini, &exec->skip, p_node->atom, exec->og_stdout);
	}
	else if (p_node->atom)
		_redirect(mini, &exec->skip, p_node->atom, exec->og_stdout);
}
