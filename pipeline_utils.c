/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:01:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:30:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_count_pipe(t_mini *mini, int (**pipefd)[2], int *pipe_nb,
		t_ast_node *first_node)
{
	t_parser_node	*p_node;
	int				i;

	*pipe_nb = 0;
	i = -1;
	while (first_node && first_node->left)
	{
		p_node = first_node->data;
		if (p_node->ops && p_node->ops == PIPE)
			(*pipe_nb)++;
		else
			break ;
		first_node = first_node->right;
	}
	*pipefd = wrap_malloc(mini,  sizeof(**pipefd) * *pipe_nb);
	while (++i < *pipe_nb)
        m_pipe(mini, pipefd, i);
}

void	_pipeline_exec_tree(t_mini *mini, t_parser_node **p_node, t_ast_node *first_node)
{
	t_ast_node	*left;

	left = first_node->left;
	_exec_tree(mini, left);
	(*p_node) = left->data;
}

void	_pipeline_skip(int i, t_ast_node **first_node, t_parser_node **p_node)
{
	int	j;

	j = -1;
	while (++j < i)
		(*first_node) = (*first_node)->right;
	(*p_node) = (*first_node)->left->data;
}

void	_pipeline_exec(t_mini *mini, t_parser_node *p_node)
{
	char	**globbed;
	char	*path;

	globbed = _glob_args(mini, _expand(mini, p_node->atom->args));
	if (check_builtin(mini, globbed[0]))
    {
		mini->status = _call_builtin(mini, globbed);
        mini->list = mini->heap_allocated.exec;
    }
	else
	{
	    close_fds(mini->fds);
		path = get_path(mini, globbed[0]);
		if (path)
			execve(path, globbed, mini->envp);
	}
}

void	__exec_pipe(t_mini *mini, t_parser_node **p_node,
		t_ast_node *first_node, t_exec *exec)
{
	redirect(mini, exec, first_node);
    if (is_op((*p_node)->ops) && !exec->skip)
        _pipeline_exec_tree(mini, p_node, first_node);
    else if (!exec->skip)
        _pipeline_exec(mini, (*p_node));
    close_fds(mini->fds);
    free_heap(mini, true);
	exit((mini->status + 256) % 256);
}
