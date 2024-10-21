/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:27:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/21 18:47:22 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

char * get_path(t_heap * heap, char * cmd);
void execution(t_heap_allocated * heap_allocated, t_ast * tree);
void	print_tree(t_heap * heap,t_ast_node * first_node);

#endif
