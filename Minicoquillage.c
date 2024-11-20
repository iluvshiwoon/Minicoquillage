/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/20 22:09:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int g_signal;

void _close(int fd)
{
    if (fd > 0)
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
    printf("\n");
    if (g_signal == 999)
        return;
    g_signal = sig; 
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
    t_mini mini;
    
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    if (MODE == INTERACTIVE && isatty(STDIN_FILENO))
    {
        if (init_alloc(&mini.heap_allocated.env) == NULL)
            return (free(mini.heap_allocated.env),EXIT_FAILURE);
        // envp = wrap_malloc(&mini.heap_allocated,heap_allocated.env,  sizeof(char *) * 3);
        // envp[0] = "hello=world";
        // envp[1] = "prout=pue";
        // envp[2] = NULL;
        incr_shlvl(&mini.heap_allocated,&envp);
        while (1)
        {
            if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
                error_exit("init_heap failed", &mini.heap_allocated);
            mini.heap_allocated.signal_status = 0;
            g_signal = 0;
            control.mini.heap_allocated = &heap_allocated;
            if(tokenizer(&control) == EXIT_SUCCESS)
                execution(&mini.heap_allocated,parser(&control),control.line, &envp);
            free_heap(&mini.heap_allocated, false);
        }
    }
    else if (MODE != INTERACTIVE)
	{
        setvbuf(stdout, NULL, _IONBF, 0); // FIXME not allowed function
        // argc = 2;
        // argv[1]= "export HOLA=bon;jour; env | grep HOLA";
        if (init_alloc(&mini.heap_allocated.env) == NULL)
            return (free(mini.heap_allocated.env),EXIT_FAILURE);
        incr_shlvl(&mini.heap_allocated,&envp);
        if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
            error_exit("init_heap failed", &mini.heap_allocated);
        mini.heap_allocated.signal_status = 0;
        g_signal = 0;
        // envp = wrap_malloc(&mini.heap_allocated,heap_allocated.ast,  sizeof(char *) * 3);
        // envp[0] = "hello=world";
        // envp[1] = "prout=pue";
        // envp[2] = NULL;
        control.mini.heap_allocated = &heap_allocated;
        if (argc == 1)
            return (EXIT_FAILURE);
		debug(argv[1],&control,&envp);
        free_heap(&mini.heap_allocated, false);
	}
	return (clear_history(),free_env(&mini.heap_allocated),0);
}
