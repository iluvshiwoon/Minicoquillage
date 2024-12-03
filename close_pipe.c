/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:58:35 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:48:29 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_close_pipe(t_mini *mini, int pipe_nb, int (*pipefd)[2])
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == 0)
		{
			m_dup2(mini, pipefd[j][1], STDOUT_FILENO);
			_close(pipefd[j][1]);
		}
		else
			_close(pipefd[j][1]);
		_close(pipefd[j][0]);
	}
}

void	_close_pipe1(t_mini *mini, int pipe_nb, int (*pipefd)[2], int i)
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == i - 1)
		{
			m_dup2(mini, pipefd[i - 1][0], STDIN_FILENO);
			_close(pipefd[i - 1][0]);
		}
		else
			_close(pipefd[j][0]);
		_close(pipefd[j][1]);
	}
}

void	_close_pipe2(t_mini *mini, int pipe_nb, int (*pipefd)[2], int i)
{
	int	j;

	j = -1;
	while (++j < pipe_nb)
	{
		if (j == i - 1)
		{
			m_dup2(mini, pipefd[i - 1][0], STDIN_FILENO);
			_close(pipefd[i - 1][0]);
		}
		else
			_close(pipefd[j][0]);
		if (j == i)
		{
			m_dup2(mini, pipefd[i][1], STDOUT_FILENO);
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

void	_close_pipes(t_mini *mini, int pipe_nb, int (*pipefd)[2], int i)
{
	if (i == 0)
		_close_pipe(mini, pipe_nb, pipefd);
	else if (i == pipe_nb)
		_close_pipe1(mini, pipe_nb, pipefd, i);
	else
		_close_pipe2(mini, pipe_nb, pipefd, i);
}
