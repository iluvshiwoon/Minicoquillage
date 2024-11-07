/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:12 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/07 14:57:56 by kgriset          ###   ########.fr       */
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
#endif
