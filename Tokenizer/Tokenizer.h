/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/29 17:54:57 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../Minicoquillage.h"

typedef enum e_token_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIRECTION,
	HERE_DOC,
	OPTION,
	AND,
	OR,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
}						t_token_type;

typedef struct s_control_dll
{
	t_double_link_list	*list;
	t_double_link_node	*node;
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

typedef struct s_token
{
	int					type;
	char				*value;
}						t_token;

// Tokenizer.c
t_double_link_list		**tokenizer(void);

// Utils_Tokenizer.c
void					init_control(t_control_dll *control);
char					*get_prompt(t_control_dll *control);
char					*init_line(t_control_dll *control, char *prompt);
char *update_node(t_control_dll *control, char *prompt, char *line);
char					*wrapper_strjoin_concat(char *s1, char *s2,
							t_double_link_list *list, t_string *string);

// Free.c
void					dl_free_list(t_double_link_list *tokens_list);
void					free_all(char **multiline,
							t_double_link_list **tokens_list, char ***tokens);

// Prompt.c
char					*build_prompt(void);
char					*last_ocur(char *string, char c);

// Utils.c
void					print_list(t_double_link_list *tokens_lists);
int						ft_isspace(int c);
size_t					count_node(t_double_link_list *list);

// Tokens.c
t_double_link_list		*create_tokens(char *line);
void					expand_tokens(t_double_link_node *node);

// Utils_Tokens.c
size_t					skip_space(char *line, size_t index);
char					*expand_double(size_t j, char *token);
char					*expand_single(size_t j, char *token);
int						expand_single_quote(size_t *j, char **token,
							char **temp, t_double_link_node **node);
int						expand_double_quote(size_t *j, char **token,
							char **temp, t_double_link_node **node);

// Utils_Tokens1.c
void					add_token(size_t i, size_t j, char *line,
							t_double_link_list *list);
int						check_quote(char c, t_open_quote *open);
size_t					init_create_tokens(t_open_quote *open,
							t_control_dll *control, char *line, size_t *j);
t_double_link_list		*expand_nodes(size_t i, size_t j,
							t_control_dll *control, char *line);
#endif
