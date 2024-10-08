/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/08 20:03:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int init_heap(t_heap_allocated * heap_allocated)
{
    if (init_alloc(&heap_allocated->Tokens) == NULL) 
        return (EXIT_FAILURE);
    if (init_alloc(&heap_allocated->AST) == NULL)
        return (free(heap_allocated->Tokens),EXIT_FAILURE);
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
            {
                parser(&control);
                dl_free_token_list(control.list);
            }
            free_heap(&heap_allocated);
        }
    }
    else 
	{
        if (argc == 1)
            return (EXIT_FAILURE);
		    debug(argv[1]);
		return (0);
	}
    printf("here\n");
	return (0);
}
