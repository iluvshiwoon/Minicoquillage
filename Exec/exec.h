/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:27:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/22 16:18:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

char * get_path(t_heap * heap, char * cmd);
void execution(t_heap_allocated * heap_allocated, t_ast * tree, char * line);
void	print_tree(t_heap * heap,t_ast_node * first_node);

// print_utils.c 
void print_t_options(t_atom * atom);
void print_t_args(t_atom * atom);
void print_t_heredoc(t_atom * atom);
void print_t_stdin(t_atom * atom);
void print_t_stdout(t_atom * atom);
void	build_tree_type(char **type);
#endif
