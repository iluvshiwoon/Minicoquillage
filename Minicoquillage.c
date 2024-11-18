/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/18 20:18:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int g_signal;

void _close(int fd, bool stdin)
{
    if (fd > 0 || stdin == true)
        close(fd);
}

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

void incr_shlvl(t_heap_allocated * heap_allocated, char *** envp)
{
    t_heap heap;
    char * shlvl;
    int value;
    int error;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->env;
    heap.env = heap_allocated->env;
    shlvl = _getenv(&heap, "SHLVL", *envp, 0);
    if (shlvl)
    {
        value = ft_atoi_safe(shlvl,&error);
        if (error == ERROR) 
            return;
        shlvl = mini_ft_itoa(&heap,value + 1);
        f_export(&heap,envp, "SHLVL=", shlvl);
    }
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
        if (init_alloc(&heap_allocated.env) == NULL)
            return (free(heap_allocated.env),EXIT_FAILURE);
        incr_shlvl(&heap_allocated,&envp);
        while (1)
        {
            if (init_heap(&heap_allocated) == EXIT_FAILURE)
                error_exit("init_heap failed", &heap_allocated);
            // envp = wrap_malloc(&heap_allocated,heap_allocated.ast,  sizeof(char *) * 3);
            // envp[0] = "hello=world";
            // envp[1] = "prout=pue";
            // envp[2] = NULL;
            heap_allocated.signal_status = 0;
            if (g_signal == SIGINT)
                heap_allocated.signal_status = 130;
            g_signal = 0;
            control.heap_allocated = &heap_allocated;
            if(tokenizer(&control) == EXIT_SUCCESS)
                execution(&heap_allocated,parser(&control),control.line, &envp);
            free_heap(&heap_allocated, false);
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
        free_heap(&heap_allocated, true);
	}
	return (clear_history(),free_env(&heap_allocated),0);
}
