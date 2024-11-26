/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:27:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 16:16:57 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

typedef struct s_exec {
    int og_stdout;
    int og_stdin;
    int skip;
} t_exec;

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

// pipeline.c
void    _count_pipe(t_heap * heap, int (**pipefd)[2], int * pipe_nb, t_ast_node * first_node);
int	_pipeline(t_mini * mini,t_ast_node * first_node,t_exec exec);

// exec.c
int	_pipeline(t_mini * mini,t_ast_node * first_node,t_exec exec);
int _call_builtin(t_mini * mini, char ** globbed, t_exec exec);
int _exec_node(t_mini * mini, char ** globbed);
void execution(t_mini * mini, t_ast * ast);

// exec_utils.c
void _reset_fd(t_exec exec);
int _call_builtin(t_mini * mini, char ** globbed, t_exec exec);

// exec_tree.c
void	_exec_tree(t_mini * mini, t_ast_node * first_node);

// redirect.c
void    _redirect(t_mini * mini, int * skip, t_atom * atom , int og_stdout);
void    redirect(t_mini * mini, t_exec * exec, t_ast_node * first_node);

// redirect_utils.c
void    _error(char * error, int * skip, int * status, char * filename, int err_status);
int     _stdin(t_heap * heap, int * skip, int * status, t_expanded * expanded, int i,t_atom * atom, int og_stdout);
int     _stdout(t_heap * heap, int * skip, int * status, t_expanded * expanded, int i, t_atom * atom, int og_stdout);
#endif
