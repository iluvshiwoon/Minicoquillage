/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/08 20:01:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

t_double_link_list * init_alloc(t_double_link_list ** list)
{
    *list = malloc(sizeof(**list));
    if (!list)
        return (NULL);
    **list = (t_double_link_list){};
    init_list(*list);
    return *list;
}

void free_heap(t_heap_allocated * heap_allocated)
{
    if (!heap_allocated)
        return;
    if (heap_allocated->Tokens)
        dl_free_list(heap_allocated->Tokens);
    if (heap_allocated->AST)
        dl_free_list(heap_allocated->AST);
}

void * wrap_malloc(t_double_link_list * heap_allocated, size_t size)
{
    t_double_link_node * new_node;

    if (!heap_allocated)
        return (NULL);
    new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return (NULL);
    *new_node = (t_double_link_node){};
    new_node->data = malloc(size);
    if (!new_node->data)
        return(free(new_node),NULL);
    heap_allocated->pf_insert_end(heap_allocated,new_node);
    return (new_node->data);
}
