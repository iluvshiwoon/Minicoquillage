/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/27 15:12:19 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# define CONTINUE 2
# include "../Minicoquillage.h"

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
}						t_token_type;

typedef enum e_quote_type
{
	NONE,
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

// assign_token.c
void					populate_first_token(t_control_dll *control);
void					populate_tokens3(t_control_dll *control,
							t_token *previous_token, size_t len_token,
							int *cmd);
void					populate_tokens2(t_control_dll *control,
							t_token *previous_token, size_t len_token,
							int *cmd);
void					populate_tokens1(t_control_dll *control,
							t_token *previous_token, size_t len_token,
							int *cmd);
void					populate_tokens(t_control_dll *control);

// assign_token_utils.c
void					populate_first_token1(t_control_dll *control,
							size_t len_token);
int						is_option(char *str);
void					add_type(t_control_dll *control, int type, int *cmd);

// check_syntax.c
int						check_syntax(char *line);
char					*concat_input(t_double_link_list *list);
int						check_temp_syntax(char *line);
int						handle_line(t_get_line *get_line,
							t_control_dll *control, int *r_value);
char					*get_line(void);

// check_syntax_utils.c
void					toggle_quote(int *quote, int *quote1);
char					*wrapper_strjoin_concat(char *s1, char *s2,
							t_double_link_list *list, t_string *string);
void					init_control(t_control_dll *control);
char					*init_line(t_control_dll *control, char *prompt);
char					*update_node(t_control_dll *control, char *prompt,
							char *line);

// check_syntax_utils1.c
size_t					count_node(t_double_link_list *list);

// Utils.c
int						ft_sep(int c);

// Error.c
void					print_error(char *error, t_control_dll *control,
							t_token *token);
int						check_error(t_control_dll *control, t_token *next);
int						check_error1(t_control_dll *control, t_token *next);
int						check_parenthesis(t_control_dll *control);
int						check_error_tokens(t_control_dll *control);

// Prompt.c
char					*get_prompt(t_control_dll *control);
char					*build_prompt(void);
char					*last_ocur(char *string, char c);

// Free.c
void					dl_free_list(t_double_link_list *tokens_list);
void					dl_free_token_list(t_double_link_list *tokens_list);

// Debug_utils.c
void					build_type(char **type);
void					print_list(t_double_link_list *tokens_lists);
void					print_csv(t_double_link_list *tokens_lists);

// Tokenizer.c
t_double_link_list		*tokenizer(void);
void					debug(char *line);

// Tokens.c
void					expand_tokens(t_double_link_node *node);
int						shenanigans(char *line, size_t *i, size_t *j,
							size_t *k);
int						is_sep(char *line, size_t *i, size_t *j,
							t_control_dll *control);
void					skip_space_wrapper(size_t j, size_t *i, char *line,
							t_open_quote *open);
t_double_link_list		*create_tokens(char *line);

// Utils_Tokens.c
size_t					skip_space(char *line, size_t index);
char					*expand_double(size_t j, char *token);
char					*expand_single(size_t j, char *token);
int						expand_single_quote(size_t *j, char **value,
							char **temp, t_double_link_node **node);
int						expand_double_quote(size_t *j, char **value,
							char **temp, t_double_link_node **node);

// Utils_Tokens1.c
void					add_token(size_t i, size_t j, char *line,
							t_control_dll *control);
int						check_quote(char c, t_open_quote *open);
size_t					init_create_tokens(t_open_quote *open,
							t_control_dll *control, char *line, size_t *j);
t_double_link_list		*expand_nodes(size_t i, size_t j,
							t_control_dll *control, char *line);

// Utils_Tokens2.c
void					init_expand(t_open_quote *open, t_control_dll *control,
							size_t *j, t_double_link_node *node);
int						handle_quote(t_control_dll *control, t_open_quote *open,
							size_t j);
int						ft_isspace(int c);
#endif
