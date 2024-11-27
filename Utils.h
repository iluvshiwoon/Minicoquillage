/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:39:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

typedef enum e_token_type
{
	R_FILE = 0,
	OPTION,
	ARG,
	OPEN_PARENTHESIS,
	COMMAND,
	CLOSE_PARENTHESIS,
	CMD_SEP,
	PIPE,
	AND,
	OR,
	REDIRECTION,
	HERE_DOC,
	EOE
}						t_token_type;

typedef enum e_quote_type
{
	NONE = 0,
	DOUBLE,
	SINGLE,
}						t_quote_type;

typedef struct s_get_line
{
	char				*prompt;
	char				*temp;
	char				*line;
}						t_get_line;

typedef struct s_token
{
	int					type;
	int					quote;
	char				*value;
}						t_token;

typedef struct s_control_dll
{
	t_double_link_list	*list;
	t_double_link_node	*node;
	t_token				*token;
	int					complete;
	char				*line;
}						t_control_dll;

typedef struct s_open_quote
{
	int					single_quote;
	int					double_quote;
}						t_open_quote;

typedef struct s_string
{
	char				*dst;
	char				*temp;
}						t_string;

typedef struct s_heap_allocated
{
	t_double_link_list	*tokens;
	t_double_link_list	*ast;
	t_double_link_list	*input;
	t_double_link_list	*exec;
	t_double_link_list	*env;
}						t_heap_allocated;

typedef struct s_heap
{
	t_heap_allocated	*heap_allocated;
	t_double_link_list	*list;
	t_double_link_list	*env;
}						t_heap;

typedef struct s_mini
{
	int					status;
	char				**envp;
	t_control_dll		control;
	t_heap_allocated	heap_allocated;
	t_heap				heap;
}						t_mini;

void					free_heap(t_heap_allocated *heap_allocated, bool all);
void					free_env(t_heap_allocated *heap_allocated);
void					error_exit(char *msg, t_heap_allocated *heap_allocated);
t_double_link_list		*init_alloc(t_double_link_list **list);
void					*wrap_malloc(t_heap_allocated *heap_allocated,
							t_double_link_list *list, size_t size);
char					*mini_ft_strjoin(t_heap_allocated *heap_allocated,
							t_double_link_list *list, char const *s1,
							char const *s2);
char					*mini_ft_strdup(t_heap_allocated *heap_allocated,
							t_double_link_list *list, const char *s);

char					**mini_ft_split(t_heap *heap, char const *s, char c);
char					*mini_ft_strtrim(t_heap *heap, char const *s1,
							char const *set);
char					*mini_ft_substr(t_heap *heap, char const *s,
							unsigned int start, size_t len);
char					*mini_ft_itoa(t_heap *heap, int n);
#endif
