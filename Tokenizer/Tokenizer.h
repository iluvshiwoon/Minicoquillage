/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 19:14:30 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# define CONTINUE 2
# ifndef MINICOQUILLAGE_H
#  include "../Minicoquillage.h"
# endif

// assign_token.c
void				populate_first_token(t_control_dll *control);
void				populate_tokens3(t_control_dll *control,
						t_token *previous_token, size_t len_token, int *cmd);
void				populate_tokens2(t_control_dll *control,
						t_token *previous_token, size_t len_token, int *cmd);
void				populate_tokens1(t_control_dll *control,
						t_token *previous_token, size_t len_token, int *cmd);
void				populate_tokens(t_control_dll *control);

// assign_token_utils.c
void				populate_first_token1(t_control_dll *control,
						size_t len_token);
int					is_option(char *str);
void				add_type(t_control_dll *control, int type, int *cmd);

// check_syntax.c
int					check_syntax(char *line);
char				*concat_input(t_heap_allocated *heap_allocated,
						t_double_link_list *list);
int					check_temp_syntax(t_mini *mini, char *line);
int					handle_line(t_mini *mini, t_get_line *get_line,
						t_double_link_list *lines, int *r_value);
char				*get_line(t_mini *mini);

// check_syntax_utils.c
void				toggle_quote(int *open_double, int *open_single, char c);
char				*wrapper_strjoin_concat(t_heap_allocated *heap_allocated,
						char *s1, char *s2, t_string *string);
void				init_control(t_mini *mini, t_control_dll *gl_control);
char				*init_line(t_heap_allocated *heap_allocated,
						t_double_link_list *lines, char *prompt);
char				*update_node(t_heap_allocated *heap_allocated,
						t_double_link_list *lines);

// check_syntax_utils1.c
size_t				count_node(t_double_link_list *list);
void				_init_get(t_mini *mini, t_double_link_list **lines,
						t_double_link_node **node, t_get_line *get_line);
void				_check(t_mini *mini, t_get_line *get_line,
						t_double_link_list *lines, int *r_value);

// Utils.c
int					ft_sep(int c);

// Error.c
void				print_error(char *error, t_token *token, int complete);
int					check_error(t_control_dll *control, t_token *next);
int					check_error1(t_control_dll *control, t_token *next);
int					check_parenthesis(t_control_dll *control);
int					check_error_tokens(t_control_dll *control);

// Prompt.c
char				*get_prompt(t_mini * mini, t_heap_allocated *heap_allocated);
char				*build_prompt(t_mini * mini, t_heap_allocated *heap_allocated);
char				*last_ocur(char *string, char c);

// Free.c
void				dl_free_list(t_double_link_list *tokens_list);
void				dl_free_token_list(t_double_link_list *tokens_list);

// Debug_utils.c
void				build_type(char **type);
void				print_list(t_double_link_list *tokens_lists);
void				print_csv(t_double_link_list *tokens_lists);

// Tokenizer.c
int					tokenizer(t_mini *mini);
void				debug(char *line, t_mini *mini);

// Tokens.c
void				expand_tokens(t_double_link_node *node);
int					shenanigans(char *line, size_t *i, size_t *j, size_t *k);
int					is_sep(char *line, size_t *i, size_t *j, t_mini *mini);
void				skip_space_wrapper(size_t j, size_t *i, char *line,
						t_open_quote *open);
t_double_link_list	*create_tokens(t_mini *mini, char *line);

// Utils_Tokens.c
size_t				skip_space(char *line, size_t index);
char				*expand_double(size_t j, char *token);
char				*expand_single(size_t j, char *token);
int					expand_single_quote(size_t *j, char **value, char **temp,
						t_double_link_node **node);
int					expand_double_quote(size_t *j, char **value, char **temp,
						t_double_link_node **node);

// Utils_Tokens1.c
void				add_token(size_t i, size_t j, char *line, t_mini *mini);
int					check_quote(char c, t_open_quote *open);
size_t				init_create_tokens(t_open_quote *open, t_mini *mini,
						char *line, size_t *j);

t_double_link_list	*expand_nodes(size_t i, size_t j, t_mini *mini, char *line);

// Utils_Tokens2.c
void				init_expand(t_open_quote *open, t_control_dll *control,
						size_t *j, t_double_link_node *node);
int					handle_quote(t_control_dll *control, t_open_quote *open,
						size_t j);
int					ft_isspace(int c);

// Utils_Tokens3.c
char				*expand_var(char *str);
int					expand(size_t *j, char **value, char **temp,
						t_double_link_node **node);
char				*expand_expand(size_t j, char *token);
char				*expand_all(char *str);

// assign_quote.c
void				assign_quote(t_double_link_node *node);

#endif
