/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:39:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/08 20:13:23 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

typedef struct s_heap_allocated {
    t_double_link_list * Tokens;
    t_double_link_list * AST;
} t_heap_allocated;


void free_heap(t_heap_allocated * heap_allocated);
void error_exit(char * msg, t_heap_allocated * heap_allocated);
t_double_link_list * init_alloc(t_double_link_list ** list);
void * wrap_malloc(t_double_link_list * heap_allocated, size_t size);

#endif
