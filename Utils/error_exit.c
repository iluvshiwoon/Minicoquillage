/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:43:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/08 19:28:43 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void error_exit(char * msg, t_heap_allocated * heap_allocated)
{
    if (msg)
        printf("%s\n", msg);
    //free heap_allocated or multiple list
    //free the list
    if (!heap_allocated)
        return;
    if (heap_allocated->Tokens)
        dl_free_list(heap_allocated->Tokens);
    if (heap_allocated->AST)
        dl_free_list(heap_allocated->AST);
}
