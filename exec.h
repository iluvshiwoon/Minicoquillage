/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:27:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/28 23:48:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

typedef struct s_exec
{
	int				og_stdout;
	int				og_stdin;
	int				skip;
	int				i;
	int				j;
    t_double_link_list * fds;
}					t_exec;

typedef struct s_pipeline
{
	int				i;
	pid_t			*pid;
	int				(*pipefd)[2];
	int				pipe_nb;
	t_parser_node	*p_node;
}					t_pipeline;

// heredoc.c
void				heredoc(t_heap *heap, t_ast_node *first_node);
size_t				_max_len(size_t len1, size_t len2);
void				clean_heredoc(t_heap *heap, t_ast_node *first_node);

// heredoc_quote.c
char				*_quote(t_heap *heap, char *to_expand);

// heredoc_clean.c
void				clean_heredoc(t_heap *heap, t_ast_node *first_node);

// heredoc_utils.c
void				mini_write(t_heap *heap, int fd, char *str, ssize_t bytes);
size_t				_max_len(size_t len1, size_t len2);
void				_write_listen(t_heap *heap, int fd, char *line);

// path.c
char				*get_path(t_heap *heap, char **envp, int *status,
						char *cmd);

// path_utils.c
bool				check_builtin(t_heap *heap, char *cmd);
bool				is_dir(char *cmd);
bool				is_path(char *cmd);

// close_pipe.c
void				_close_pipes(int pipe_nb, int (*pipefd)[2], int i);
void				_close_pipe3(int pipe_nb, int (*pipefd)[2], int i);

// pipeline_utils.c
void				_count_pipe(t_heap *heap, int (**pipefd)[2], int *pipe_nb,
						t_ast_node *first_node);
void	_pipeline_exec_tree(t_mini *mini, t_parser_node **p_node,
		t_ast_node *first_node, t_exec exec);
void				_pipeline_skip(int i, t_ast_node **first_node,
						t_parser_node **p_node);
void				_pipeline_exec(t_mini *mini, t_parser_node *p_node);
void				__exec_pipe(t_mini *mini, t_parser_node **p_node,
						t_ast_node *first_node, t_exec *exec);

// pipeline.c
void				_count_pipe(t_heap *heap, int (**pipefd)[2], int *pipe_nb,
						t_ast_node *first_node);
int					_pipeline(t_mini *mini, t_ast_node *first_node,
						t_exec exec);

// exec.c
int					_pipeline(t_mini *mini, t_ast_node *first_node,
						t_exec exec);
int					_call_builtin(t_mini *mini, char **globbed, t_exec exec);
int					_exec_node(t_mini *mini, char **globbed);
void				execution(t_mini *mini, t_ast *ast);

// exec_utils.c
void				_reset_fd(t_exec exec);
int					_call_builtin(t_mini *mini, char **globbed, t_exec exec);
void    __dup(t_mini * mini, t_exec * exec);

// exec_tree.c
void				_exec_tree(t_mini *mini, t_ast_node *first_node, t_double_link_list * fds);

// redirect.c
void				_redirect(t_mini *mini, t_atom *atom, t_exec *exec);
void				redirect(t_mini *mini, t_exec *exec,
						t_ast_node *first_node);

// redirect_utils.c
int					_stdin(t_mini *mini, t_expanded *expanded, t_atom *atom,
						t_exec *exec);
int					_stdout(t_mini *mini, t_expanded *expanded, t_atom *atom,
						t_exec *exec);

// redirect_utils1.c
void				_error(char *error, int *skip, int *status, char *filename);
void				__red(char *globbed, t_atom *atom, t_exec *exec);

void    close_fds(t_double_link_list * fds);
#endif
