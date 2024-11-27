/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:19:02 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_clean(t_heap *heap, t_ast_node *first_node)
{
	t_ast_node		*left;
	t_parser_node	*p_node;

	left = first_node->left;
	p_node = left->data;
	if (is_op(p_node->ops))
		clean_heredoc(heap, left);
	else if (p_node->atom->heredoc)
	{
		if (p_node->atom->in_fd)
			_close(p_node->atom->in_fd);
		if (p_node->atom->file_heredoc)
			unlink(p_node->atom->file_heredoc);
	}
	p_node = first_node->data;
	if (p_node->ops)
	{
		if (p_node->atom && p_node->atom->heredoc)
		{
			if (p_node->atom->in_fd)
				_close(p_node->atom->in_fd);
			if (p_node->atom->file_heredoc)
				unlink(p_node->atom->file_heredoc);
		}
	}
}

void	clean_heredoc(t_heap *heap, t_ast_node *first_node)
{
	while (first_node && first_node->left)
	{
		_clean(heap, first_node);
		first_node = first_node->right;
	}
}
