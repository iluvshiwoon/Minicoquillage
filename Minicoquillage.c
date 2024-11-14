/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/14 16:36:20 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int g_signal;

int init_heap(t_heap_allocated * heap_allocated)
{
    if (init_alloc(&heap_allocated->tokens) == NULL) 
        return (EXIT_FAILURE);
    if (init_alloc(&heap_allocated->ast) == NULL)
        return (free(heap_allocated->tokens),EXIT_FAILURE);
    if (init_alloc(&heap_allocated->input) == NULL)
        return (free(heap_allocated->input),EXIT_FAILURE);
    if (init_alloc(&heap_allocated->exec) == NULL)
        return (free(heap_allocated->exec),EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void sigint_handler(int sig)
{
    g_signal = sig; 
    printf("\n");
    close(STDIN_FILENO);
}

int	main(int argc, char **argv, char ** envp)
{
    struct sigaction sa;
	t_control_dll	control;
    t_heap_allocated heap_allocated;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    if (MODE == INTERACTIVE && isatty(STDIN_FILENO))
    {
        while (1)
        {
            if (init_heap(&heap_allocated) == EXIT_FAILURE)
                error_exit("init_heap failed", &heap_allocated);
            heap_allocated.signal_status = 0;
            if (g_signal == SIGINT)
                heap_allocated.signal_status = 130;
            g_signal = 0;
            control.heap_allocated = &heap_allocated;
            if(tokenizer(&control) == EXIT_SUCCESS)
                execution(&heap_allocated,parser(&control),control.line, envp);
            free_heap(&heap_allocated);
        }
    }
    else if (MODE != INTERACTIVE)
	{
        if (init_heap(&heap_allocated) == EXIT_FAILURE)
            error_exit("init_heap failed", &heap_allocated);
        control.heap_allocated = &heap_allocated;
        if (argc == 1)
            return (EXIT_FAILURE);
		    debug(argv[1],&control);
        free_heap(&heap_allocated);
	}
	return (clear_history(),EXIT_SUCCESS);
}
