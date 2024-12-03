/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 04:07:26 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int		g_signal;

void	_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	init_heap(t_mini *mini)
{
	if (init_alloc(&mini->heap_allocated.tokens) == NULL)
		return (EXIT_FAILURE);
	if (init_alloc(&mini->heap_allocated.ast) == NULL)
		return (free(mini->heap_allocated.tokens), EXIT_FAILURE);
	if (init_alloc(&mini->heap_allocated.input) == NULL)
		return (free(mini->heap_allocated.input), EXIT_FAILURE);
	if (init_alloc(&mini->heap_allocated.exec) == NULL)
		return (free(mini->heap_allocated.exec), EXIT_FAILURE);
	if (init_alloc(&mini->fds) == NULL)
		return (free(mini->fds), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	incr_shlvl(t_mini *mini)
{
	char	*shlvl;
	int		value;
	int		error;

	mini->list = mini->heap_allocated.env;
	shlvl = _getenv(mini, "SHLVL");
	if (shlvl)
	{
		value = ft_atoi_safe(shlvl, &error);
		if (error == ERROR)
			return ;
		shlvl = mini_ft_itoa(mini, value + 1);
		f_export(mini, "SHLVL=", shlvl);
	}
}

char	**init_env(t_mini *mini)
{
	char	**new_env;

	mini->list = mini->heap_allocated.env;
	new_env = wrap_malloc(mini, sizeof(char *) * 4);
	new_env[0] = mini_ft_strdup(mini, "SHLVL=1");
	new_env[1] = mini_ft_strdup(mini, "PATH=/usr/local/sbin:/usr/lo\
cal/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	new_env[2] = mini_ft_strdup(mini, "SHELL=env");
	new_env[3] = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	mini = (t_mini){};
	handle_sig();
	if (MODE == INTERACTIVE && isatty(STDIN_FILENO))
	{
		if (init_alloc(&mini.heap_allocated.env) == NULL)
			return (free(mini.heap_allocated.env), EXIT_FAILURE);
		mini.envp = envp;
		if (!envp || !envp[0])
			mini.envp = init_env(&mini);
		incr_shlvl(&mini);
		while (1)
		{
			if (init_heap(&mini) == EXIT_FAILURE)
				error_exit("init_heap failed", &mini);
			if (g_signal == SIGINT)
				mini.status = 130;
			g_signal = 0;
			if (tokenizer(&mini) == EXIT_SUCCESS)
				execution(&mini, parser(&mini));
			free_heap(&mini, false);
		}
	}
	else if (MODE != INTERACTIVE)
	{
		setvbuf(stdout, NULL, _IONBF, 0); // FIXME not allowed function
		if (init_alloc(&mini.heap_allocated.env) == NULL)
			return (free(mini.heap_allocated.env), EXIT_FAILURE);
		mini.envp = envp;
		if (!envp || !envp[0])
			mini.envp = init_env(&mini);
		incr_shlvl(&mini);
		if (init_heap(&mini) == EXIT_FAILURE)
			error_exit("init_heap failed", &mini);
		g_signal = 0;
		if (argc == 1)
			return (EXIT_FAILURE);
		debug(argv[1], &mini);
		return (free_heap(&mini, true), mini.status);
	}
	return (clear_history(), free_all(&mini), mini.status);
}
