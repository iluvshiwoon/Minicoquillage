/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:37:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/15 13:46:46 by kgriset          ###   ########.fr       */
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
    if (heap_allocated->tokens)
        dl_free_list(heap_allocated->tokens);
    if (heap_allocated->ast)
        dl_free_list(heap_allocated->ast);
    if (heap_allocated->input)
        dl_free_list(heap_allocated->input);
}

void * wrap_malloc(t_heap_allocated * heap_allocated, t_double_link_list * list, size_t size)
{
    t_double_link_node * new_node;

    if (!list || !heap_allocated)
        return (free_heap(heap_allocated),exit(EXIT_FAILURE),NULL);
    new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return (free_heap(heap_allocated),exit(EXIT_FAILURE),NULL);
    *new_node = (t_double_link_node){};
    new_node->data = malloc(size);
    if (!new_node->data)
        return(free(new_node),free_heap(heap_allocated),exit(EXIT_FAILURE),NULL);
    list->pf_insert_end(list,new_node);
    return (new_node->data);
}


