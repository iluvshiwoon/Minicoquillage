/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:43:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/15 13:39:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void error_exit(char * msg, t_heap_allocated * heap_allocated)
{
    if (msg)
        perror(msg);
    free_heap(heap_allocated);
    exit(EXIT_FAILURE);
}
