#ifndef TOKENIZER_H
# define TOKENIZER_H

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
	CMD_SEP
}						t_token_type;

typedef struct s_token
{
	int					type;
	char				*value;
}						t_token;

typedef struct s_control_dll
{
	t_double_link_list	*list;
	t_double_link_node	*node;
    t_token * token;
}						t_control_dll;

#endif
