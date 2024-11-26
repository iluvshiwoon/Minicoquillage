/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:34:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 22:22:57 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

t_expanded *    _init_dosplit(t_heap * heap, char * str, bool * litteral)
{
    t_expanded * expanded;
    int count;
    int i;
    int j;

    expanded = wrap_malloc(heap->heap_allocated, heap->list,sizeof(*expanded));
    count = _count_split(str, litteral);
    if (!count)
        count = 1;
    expanded->value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*expanded->value) * (count + 1));
    expanded->litteral = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*expanded->litteral) * count);
    expanded->value[count] = NULL;
    i= 0;
    j = -1;
    if (!str[i])
    { 
        expanded->value[++j] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char));
        expanded->litteral[j] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(bool));
        expanded->value[j][0] = '\0';
        expanded->litteral[j][0] = true;
    }
    return (expanded);
}

void __init(t_heap * heap, t_to_expand* to_expand, t_expanded ** expanded, t_index * index)
{
    index->i = 0;
    index->j = -1;
    *expanded = _init_dosplit(heap, to_expand->str, to_expand->litteral);
    index->count = 0;
}

t_expanded * _do_split(t_heap * heap, t_to_expand * to_expand)
{
    t_index index;
    t_expanded * expanded;

    __init(heap, to_expand, &expanded, &index);
    while (to_expand->str[index.i])
    {
        index.k = index.i;
        if (to_expand->str[index.i] && (!ft_isspace(to_expand->str[index.i]) || to_expand->litteral[index.i]))
        {
            while(to_expand->str[index.i] && (!ft_isspace(to_expand->str[index.i]) || to_expand->litteral[index.i]))
            {
                index.i++;
                index.count++;
            }
        }
        else
        {
            while(to_expand->str[index.i] && ft_isspace(to_expand->str[index.i]) && !to_expand->litteral[index.i])
                index.i++;
        }
        _assign_value(heap, &expanded, &index,to_expand);
        if (!to_expand->str[index.i])
            break;
    }
    return expanded;
}

t_expanded * _assign_split(t_heap * heap, t_expanded * expanded, int count)
{
    t_expanded * r_value;
    t_expanded * splitted;
    t_to_expand to_expand;
    t_index index;

    r_value = wrap_malloc(heap->heap_allocated, heap->list,sizeof(*expanded));
    r_value->value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*r_value->value) * (count + 1));
    r_value->litteral = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*r_value->litteral) * (count));
    r_value->value[count] = NULL;
    index.i = -1;
    index.j = -1;
    while (expanded->value[++index.i])
    {
        index.k = -1;
        to_expand.litteral = expanded->litteral[index.i];
        to_expand.str = expanded->value[index.i];
        splitted = _do_split(heap,&to_expand);
        while (splitted->value[++index.k])
        {
            r_value->value[++index.j] = splitted->value[index.k];
            r_value->litteral[index.j] = splitted->litteral[index.k];
        }
    }
    return (r_value);
}

t_expanded * _split_arg(t_heap * heap, t_expanded * expanded)
{
    t_index index;
    int count; 

    index.i = -1;
    count = 0;
    while (expanded->value[++index.i])
    {
        index.j = _count_split(expanded->value[index.i], expanded->litteral[index.i]);
        if (index.j)
            count += index.j;
        else 
            count++;
    }
    return (_assign_split(heap, expanded, count));
}
