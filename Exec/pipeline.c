/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:00:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 17:12:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
		if (pipeline->pid[pipeline->i] == 0)
		{
			_close_pipes(pipeline->pipe_nb, pipeline->pipefd, pipeline->i);
			_pipeline_skip(pipeline->i, &first_node, &pipeline->p_node);
			__exec_pipe(mini, &pipeline->p_node, first_node, &exec);
		}
		else
			_close_pipe3(pipeline->pipe_nb, pipeline->pipefd, pipeline->i);
	}
	pipeline->i = -1;
}

int	_pipeline(t_mini *mini, t_ast_node *first_node, t_exec exec)
{
	t_pipeline	pipeline;
	int			err;

	_run_pipeline(mini, first_node, exec, &pipeline);
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
