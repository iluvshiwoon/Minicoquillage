/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 00:38:40 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_count_pipe(t_heap *heap, int (**pipefd)[2], int *pipe_nb,
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
	*pipefd = wrap_malloc(heap->heap_allocated, heap->list, sizeof(**pipefd)
			* *pipe_nb);
	while (++i < *pipe_nb)
	{
		if (pipe((*pipefd)[i]) == -1) // FIXME
			perror("pipe");
	}
}

void	_close_pipe(int pipe_nb, int (*pipefd)[2])
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == 0)
		{
			dup2(pipefd[j][1], STDOUT_FILENO);
			_close(pipefd[j][1]);
		}
		else
			_close(pipefd[j][1]);
		_close(pipefd[j][0]);
	}
}

void	_close_pipe1(int pipe_nb, int (*pipefd)[2], int i)
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == i - 1)
		{
			dup2(pipefd[i - 1][0], STDIN_FILENO);
			_close(pipefd[i - 1][0]);
		}
		else
			_close(pipefd[j][0]);
		_close(pipefd[j][1]);
	}
}

void	_close_pipe2(int pipe_nb, int (*pipefd)[2], int i)
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == i - 1)
		{
			dup2(pipefd[i - 1][0], STDIN_FILENO);
			_close(pipefd[i - 1][0]);
		}
		else
			_close(pipefd[j][0]);
		if (j == i)
		{
			dup2(pipefd[i][1], STDOUT_FILENO);
			_close(pipefd[i][1]);
		}
		else
			_close(pipefd[j][1]);
	}
}

void	_close_pipe3(int pipe_nb, int (*pipefd)[2], int i)
{
	if (i == 0)
		_close(pipefd[i][1]);
	else if (i == pipe_nb)
		_close(pipefd[i - 1][0]);
	else
	{
		_close(pipefd[i - 1][0]);
		_close(pipefd[i][1]);
	}
}

void	_pipeline_exec_tree(t_mini *mini, t_parser_node **p_node,
		t_ast_node *first_node)
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
	globbed = _glob_args(&mini->heap, _expand(mini, p_node->atom->args));
	if (check_builtin(&mini->heap, globbed[0]))
		mini->status = _call_builtin(mini, globbed, exec);
	else
	{
		path = get_path(&mini->heap, mini->envp, &mini->status, globbed[0]);
		if (path)
			execve(path, globbed, mini->envp);
	}
	if (p_node->atom && p_node->atom->in_fd)
		_close(p_node->atom->in_fd);
	if (p_node->atom && p_node->atom->out_fd)
		_close(p_node->atom->out_fd);
}

void	_close_pipes(int pipe_nb, int (*pipefd)[2], int i)
{
	if (i == 0)
		_close_pipe(pipe_nb, pipefd);
	else if (i == pipe_nb)
		_close_pipe1(pipe_nb, pipefd, i);
	else
		_close_pipe2(pipe_nb, pipefd, i);
}

void	__exec_pipe(t_mini *mini, t_parser_node **p_node,
		t_ast_node *first_node, t_exec *exec)
{
	redirect(mini, exec, first_node);
	_close(exec->og_stdin);
	_close(exec->og_stdout);
	if (is_op((*p_node)->ops) && !exec->skip)
		_pipeline_exec_tree(mini, p_node, first_node);
	else if (!exec->skip)
		_pipeline_exec(mini, (*p_node));
	free_heap(&mini->heap_allocated, true);
	exit((mini->status + 256) % 256);
}

void	_run_pipeline(t_mini *mini, t_ast_node *first_node, t_exec exec,
		t_pipeline *pipeline)
{
	pipeline->i = -1;
	exec.skip = 0;
	_count_pipe(&mini->heap, &pipeline->pipefd, &pipeline->pipe_nb, first_node);
	pipeline->pid = wrap_malloc(&mini->heap_allocated,
			mini->heap_allocated.exec, sizeof(pid_t) * (pipeline->pipe_nb + 1));
	while (++pipeline->i < pipeline->pipe_nb + 1)
	{
		pipeline->pid[pipeline->i] = fork();
		// same as for open wrapper for failure;
		if (pipeline->pid[pipeline->i] == 0)
		{
			_close_pipes(pipeline->pipe_nb, pipeline->pipefd, pipeline->i);
			_pipeline_skip(pipeline->i, &first_node, &pipeline->p_node);
			__exec_pipe(mini, &pipeline->p_node, first_node, &exec);
		}
		else
			_close_pipe3(pipeline->pipe_nb, pipeline->pipefd, pipeline->i);
	}
}

int	_pipeline(t_mini *mini, t_ast_node *first_node, t_exec exec)
{
	t_pipeline	pipeline;
	int			err;

	_run_pipeline(mini, first_node, exec, &pipeline);
	pipeline.i = -1;
	while (++(pipeline.i) < pipeline.pipe_nb + 1)
	{
		while (1)
		{
			err = waitpid(pipeline.pid[pipeline.i], &mini->status, 0);
			if (err == -1)
			{
				if (errno == EINTR)
					continue ;
				else
					error_exit(strerror(errno), &mini->heap_allocated);
			}
			else if (WIFEXITED(mini->status) || WIFSIGNALED(mini->status))
				break ;
		}
	}
	if (WIFEXITED(mini->status))
		return (WEXITSTATUS(mini->status));
	else if (WIFSIGNALED(mini->status))
		return (128 + WTERMSIG(mini->status));
	return (error_exit("pipeline failure\n", &mini->heap_allocated), 999);
}
