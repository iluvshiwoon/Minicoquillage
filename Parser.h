/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

typedef struct s_atom
{
	char			*cmd;
	char			**options;
	char			**args;
	char			**heredoc_eof;
	char			**std_out;
	char			**std_in;
	char			*std_order;
	bool			*append;
	bool			heredoc;
	int				in_fd;
	int				out_fd;
	char			*file_heredoc;
}					t_atom;

typedef struct s_parser_node
{
	int				ops;
	t_atom			*atom;
}					t_parser_node;

typedef struct s_token_count
{
	int				cmd;
	int				options;
	int				args;
	int				heredoc_eof;
	int				std_out;
	int				std_in;
}					t_token_count;

// parser_utils.c
bool				is_op(int type);
t_double_link_node	*get_next_op(t_mini *mini, t_double_link_node *beg,
						t_double_link_node *end);
void				count_token(t_double_link_node *beg,
						t_double_link_node *end, t_token_count *count);
void				alloc_atom(t_mini *mini, t_token_count count, t_atom *atom);
int					fill_atom(t_mini *mini, t_ast_node **current_node,
						t_double_link_node *beg, t_double_link_node *end);

// atom.c
void				fill_in(t_atom *atom, t_double_link_node *beg,
						t_double_link_node *end);
int					compute_atom(t_mini *mini, t_double_link_node *beg,
						t_double_link_node *end, t_ast_node **current_node);

// parser.c
t_ast				*parser(t_mini *mini);
void				skip_through(t_mini *mini, t_parser_node *p_node,
						t_double_link_node *next_op);
t_double_link_node	*get_next_op(t_mini *mini, t_double_link_node *beg,
						t_double_link_node *end);
void				compute_expr(t_mini *mini, t_double_link_node *beg,
						t_double_link_node *end, t_ast_node *current_node);

#endif
