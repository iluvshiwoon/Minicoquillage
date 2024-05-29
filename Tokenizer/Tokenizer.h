#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../Minicoquillage.h"

typedef enum e_token_type {
    COMMAND, // relative or absolute if needed
    ARG,
    PIPE,
    REDIRECTION,
    HERE_DOC,
    OPTION,
    AND,
    OR,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
} t_token_type;

typedef struct s_token {
    int type;
    char * value;
} t_token;

// Tokenizer.c
t_double_link_list ** tokenizer(void);

// Free.c
void dl_free_list(t_double_link_list * tokens_list);
void free_all(char ** multiline, t_double_link_list ** tokens_list, char *** tokens);

// Prompt.c
char * build_prompt();
char * last_ocur (char * string , char c);

// Utils.c
void print_tokens_list(t_double_link_list ** tokens_lists);
void print_list(t_double_link_list * tokens_lists);
int ft_isspace(int c);

// Tokens.c 
t_double_link_list * create_tokens(char * line);
size_t skip_space(char * line, size_t index);
void add_token(size_t i, size_t j, char * line, t_double_link_list * list);
char * expand_double(size_t j, char * token);
char * expand_single(size_t j, char * token);
void expand_tokens(t_double_link_node * node);

#endif
