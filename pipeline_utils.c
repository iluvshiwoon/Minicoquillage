/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:01:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 04:21:29 by kgriset          ###   ########.fr       */
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
	{
		if (pipe((*pipefd)[i]) == -1)
			error_exit(strerror(errno), mini);
	}
}

void	_pipeline_exec_tree(t_mini *mini, t_parser_node **p_node, t_ast_node *first_node)
{
	t_ast_node	*left;

	left = first_node->left;
	_exec_tree(mini, left);
	(*p_node) = first_node->data;
	if ((*p_node)->atom && (*p_node)->atom->in_fd)
		_close((*p_node)->atom->in_fd);
	if ((*p_node)->atom && (*p_node)->atom->out_fd)
		_close((*p_node)->atom->out_fd);
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
	t_exec	exec;
	char	**globbed;
	char	*path;

	exec.og_stdin = 0;
	exec.og_stdout = 0;
	globbed = _glob_args(mini, _expand(mini, p_node->atom->args));
	if (check_builtin(mini, globbed[0]))
    {
		mini->status = _call_builtin(mini, globbed, exec);
        mini->list = mini->heap_allocated.exec;
    }
	else
	{
		path = get_path(mini, globbed[0]);
		if (path)
			execve(path, globbed, mini->envp);
	}
	if (p_node->atom && p_node->atom->in_fd)
		_close(p_node->atom->in_fd);
	if (p_node->atom && p_node->atom->out_fd)
		_close(p_node->atom->out_fd);
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
