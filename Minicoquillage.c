/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/21 02:36:59 by kgriset          ###   ########.fr       */
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

void incr_shlvl(t_mini * mini)
{
    t_heap heap;
    char * shlvl;
    int value;
    int error;

    heap.heap_allocated = &mini->heap_allocated;
    heap.list = mini->heap_allocated.env;
    heap.env = mini->heap_allocated.env;
    shlvl = _getenv(&heap, "SHLVL", mini->envp, 0);
    if (shlvl)
    {
        value = ft_atoi_safe(shlvl,&error);
        if (error == ERROR) 
            return;
        shlvl = mini_ft_itoa(&heap,value + 1);
        f_export(&heap,&mini->envp, "SHLVL=", shlvl);
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
    mini.envp = envp;
    if (MODE == INTERACTIVE && isatty(STDIN_FILENO))
    {
        if (init_alloc(&mini.heap_allocated.env) == NULL)
            return (free(mini.heap_allocated.env),EXIT_FAILURE);
        // envp = wrap_malloc(&mini.heap_allocated,heap_allocated.env,  sizeof(char *) * 3);
        // envp[0] = "hello=world";
        // envp[1] = "prout=pue";
        // envp[2] = NULL;
        incr_shlvl(&mini);
        while (1)
        {
            if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
                error_exit("init_heap failed", &mini.heap_allocated);
            g_signal = 0;
            // control.mini.heap_allocated = &heap_allocated;
            if(tokenizer(&mini) == EXIT_SUCCESS)
                execution(&mini,parser(&mini));
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
        incr_shlvl(&mini);
        if (init_heap(&mini.heap_allocated) == EXIT_FAILURE)
            error_exit("init_heap failed", &mini.heap_allocated);
        g_signal = 0;
        // envp = wrap_malloc(&mini.heap_allocated,heap_allocated.ast,  sizeof(char *) * 3);
        // envp[0] = "hello=world";
        // envp[1] = "prout=pue";
        // envp[2] = NULL;
        // control.mini.heap_allocated = &heap_allocated;
        if (argc == 1)
            return (EXIT_FAILURE);
		debug(argv[1],&mini);
        return(free_heap(&mini.heap_allocated, true),mini.status);
	}
	return (clear_history(),free_env(&mini.heap_allocated),0);
}
