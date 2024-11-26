/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:27:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 11:42:46 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

void execution(t_mini * mini, t_ast * ast);

// heredoc.c
void	heredoc(t_heap * heap,t_ast_node * first_node);
size_t _max_len(size_t len1, size_t len2);
void	clean_heredoc(t_heap * heap,t_ast_node * first_node);

// heredoc_quote.c
char * _quote(t_heap * heap, char * to_expand);

// heredoc_clean.c
void	clean_heredoc(t_heap * heap,t_ast_node * first_node);

// heredoc_utils.c
void mini_write(t_heap * heap,int fd, char * str, ssize_t bytes);
size_t _max_len(size_t len1, size_t len2);
void    _write_listen(t_heap * heap, int fd, char * line);

// path.c
char * get_path(t_heap * heap,char ** envp,int * status, char * cmd);

// path_utils.c
bool check_builtin(t_heap* heap, char * cmd);
bool is_dir(char * cmd);
bool is_path(char * cmd);
#endif
