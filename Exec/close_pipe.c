/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:58:35 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 15:59:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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

void	_close_pipes(int pipe_nb, int (*pipefd)[2], int i)
{
	if (i == 0)
		_close_pipe(pipe_nb, pipefd);
	else if (i == pipe_nb)
		_close_pipe1(pipe_nb, pipefd, i);
	else
		_close_pipe2(pipe_nb, pipefd, i);
}
