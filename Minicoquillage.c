/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 20:35:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int		g_signal;

void	_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	init_heap(t_heap_allocated *heap_allocated)
{
	if (init_alloc(&heap_allocated->tokens) == NULL)
		return (EXIT_FAILURE);
	if (init_alloc(&heap_allocated->ast) == NULL)
		return (free(heap_allocated->tokens), EXIT_FAILURE);
	if (init_alloc(&heap_allocated->input) == NULL)
		return (free(heap_allocated->input), EXIT_FAILURE);
	if (init_alloc(&heap_allocated->exec) == NULL)
		return (free(heap_allocated->exec), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	incr_shlvl(t_mini *mini)
{
	t_heap	heap;
	char	*shlvl;
	int		value;
	int		error;

	heap.heap_allocated = &mini->heap_allocated;
	heap.list = mini->heap_allocated.env;
	heap.env = mini->heap_allocated.env;
	shlvl = _getenv(&heap, "SHLVL", mini->envp, 0);
	if (shlvl)
	{
		value = ft_atoi_safe(shlvl, &error);
		if (error == ERROR)
			return ;
		shlvl = mini_ft_itoa(&heap, value + 1);
		f_export(&heap, &mini->envp, "SHLVL=", shlvl);
	}
}

char	**init_env(t_mini *mini)
{
	char	**new_env;

	new_env = wrap_malloc(&mini->heap_allocated, mini->heap_allocated.env,
			sizeof(char *) * 4);
	new_env[0] = mini_ft_strdup(&mini->heap_allocated, mini->heap_allocated.env,
			"SHLVL=1");
	new_env[1] = mini_ft_strdup(&mini->heap_allocated, mini->heap_allocated.env,
			"PATH=/usr/local/sbin:/usr/lo\
cal/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	new_env[2] = mini_ft_strdup(&mini->heap_allocated, mini->heap_allocated.env,
			"SHELL=env");
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
			if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
				error_exit("init_heap failed", &mini.heap_allocated);
			g_signal = 0;
			if (tokenizer(&mini) == EXIT_SUCCESS)
				execution(&mini, parser(&mini));
			free_heap(&mini.heap_allocated, false);
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
		if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
			error_exit("init_heap failed", &mini.heap_allocated);
		g_signal = 0;
		if (argc == 1)
			return (EXIT_FAILURE);
		debug(argv[1], &mini);
		return (free_heap(&mini.heap_allocated, true), mini.status);
	}
	return (clear_history(), free_env(&mini.heap_allocated), 0);
}
