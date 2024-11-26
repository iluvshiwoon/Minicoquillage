/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:21:25 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 22:22:22 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int _count_split(char * str, bool * litteral)
{
    int count;
    int i;

    count = 0;
    i= 0;
    while (str[i])
    {
        if (str[i] && (!ft_isspace(str[i]) || litteral[i]))
        {
            while(str[i] && (!ft_isspace(str[i]) || litteral[i]))
                i++;
            count++;
        }
        else
        {
            while(str[i] && ft_isspace(str[i]) && !litteral[i])
                i++;
        }
        if (!str[i])
            break;
    }
    return (count);
}

void    _assign_value(t_heap * heap, t_expanded ** expanded, t_index * index,t_to_expand * to_expand)
{
    if (index->count)
    {
        (*expanded)->value[++index->j]=wrap_malloc(heap->heap_allocated,heap->list, sizeof(*(*expanded)->value) * (index->count + 1));
        (*expanded)->litteral[index->j]=wrap_malloc(heap->heap_allocated,heap->list, sizeof(*(*expanded)->litteral) * (index->count));
        (*expanded)->value[index->j][index->count] = '\0';
        ft_strlcpy((*expanded)->value[index->j],to_expand->str+index->i-index->count,index->count + 1);
        int m = -1;
        while (index->count > 0)
        {
            index->count--;
            (*expanded)->litteral[index->j][++m] = to_expand->litteral[index->k];
            index->k++;
        }
        index->count = 0;
    }
}
