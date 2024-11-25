/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:12 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 11:27:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

typedef struct s_expanded {
    char ** value;
    bool ** litteral;
} t_expanded;

t_expanded * _expand(t_heap * heap, char ** to_expand, char ** envp, int status);
char ** _glob_args(t_heap * heap, t_expanded * expanded);
int _count_glob(t_heap * heap, char * str, bool * litteral);
char * _getenv(t_heap * heap, char * var, char ** envp, int status);
int	_handle_quote(char c, t_open_quote *open);
#endif
