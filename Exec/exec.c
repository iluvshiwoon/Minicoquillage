/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/22 16:22:05 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void execution(t_heap_allocated * heap_allocated, t_ast * ast, char * line)
{
    t_heap heap;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->exec;
    print_tree(&heap,ast->first_node);
    printf("\n");
    add_history(line);
}
