/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:39:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/21 18:16:02 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

typedef struct s_heap_allocated {
    t_double_link_list * tokens;
    t_double_link_list * ast;
    t_double_link_list * input;
    t_double_link_list * exec;
} t_heap_allocated;

typedef struct s_heap {
    t_heap_allocated * heap_allocated;
    t_double_link_list * list;
} t_heap;

void free_heap(t_heap_allocated * heap_allocated);
void error_exit(char * msg, t_heap_allocated * heap_allocated);
t_double_link_list * init_alloc(t_double_link_list ** list);
void * wrap_malloc(t_heap_allocated * heap_allocated, t_double_link_list * list, size_t size);
char	*mini_ft_strjoin(t_heap_allocated * heap_allocated, t_double_link_list * list, char const *s1, char const *s2);
char	*mini_ft_strdup(t_heap_allocated * heap_allocated, t_double_link_list * list,const char *s);


char	**mini_ft_split(t_heap * heap,char const *s, char c);
char	*mini_ft_strtrim(t_heap * heap, char const *s1, char const *set);
char	*mini_ft_substr(t_heap * heap,char const *s, unsigned int start, size_t len);
#endif
