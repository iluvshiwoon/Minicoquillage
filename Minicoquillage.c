/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/21 18:02:57 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

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

int	main(int argc, char **argv)
{
	t_control_dll	control;
    t_heap_allocated heap_allocated;

    if (MODE == INTERACTIVE)
    {
        while (1)
        {
            if (init_heap(&heap_allocated) == EXIT_FAILURE)
                error_exit("init_heap failed", &heap_allocated);
            control.heap_allocated = &heap_allocated;
            if(tokenizer(&control) == EXIT_SUCCESS)
                execution(&heap_allocated,parser(&control));
            free_heap(&heap_allocated);
        }
    }
    else 
	{
        if (init_heap(&heap_allocated) == EXIT_FAILURE)
            error_exit("init_heap failed", &heap_allocated);
        control.heap_allocated = &heap_allocated;
        if (argc == 1)
            return (EXIT_FAILURE);
		    debug(argv[1],&control);
        free_heap(&heap_allocated);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
