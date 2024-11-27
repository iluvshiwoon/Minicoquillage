/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:12 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
	int				count;
}					t_index;

typedef struct s_expanded
{
	char			**value;
	bool			**litteral;
}					t_expanded;

typedef struct s_to_expand
{
	char			*str;
	bool			*litteral;
	t_open_quote	open;
	int				status;
}					t_to_expand;

// expand_utils.c
char				*var_name(t_heap *heap, char *var);
char				*_getenv(t_heap *heap, char *var, char **envp, int status);
bool				_is_empty_quote(t_mini *mini, char *to_expand);
void				_init_expand(t_mini *mini, char **to_expand,
						t_expanded *expanded, int status);
int					_handle_quote(char c, t_open_quote *open);

// exp_glob.c
int					_count_glob(t_heap *heap, char *str, bool *litteral);
char				**_glob_args(t_heap *heap, t_expanded *expanded);

// exp_split.c
int					_count_split(char *str, bool *litteral);
t_expanded			*_do_split(t_heap *heap, t_to_expand *to_expand);
t_expanded			*_split_arg(t_heap *heap, t_expanded *expanded);

// exp_split_utils.c
int					_count_split(char *str, bool *litteral);
void				_assign_value(t_heap *heap, t_expanded **expanded,
						t_index *index, t_to_expand *to_expand);
void				__ass_split(t_expanded *r, t_expanded *splitted,
						t_index *index);
void				__do(t_index *index);

// exp_exp.c
char				*_assign_exp(t_mini *mini, char *str, int *i,
						t_to_expand _expand);
int					_count_exp(t_mini *mini, char *str, int *i,
						t_to_expand _expand);
bool				_is_valid_exp(char c);
void				init_ass(int *k, int i, char **r_value, char **var);

// expand.c
void				_assign(t_mini *mini, char *to_expand,
						t_to_expand *_expand);
t_expanded			*_expand(t_mini *mini, char **to_expand);
int					_count(t_mini *mini, char *str, int status);

// expand_utils1.c
void				mod_expand(t_to_expand *expand, int status,
						t_open_quote open);

#endif
