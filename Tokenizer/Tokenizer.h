#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../Minicoquillage.h"
typedef enum e_token_type {
    COMMAND, // relative or absolute if needed
    LITTERAL, //need to be concatened with something
    EXPANSION,
    ARG,
    PIPE,
    REDIRECTION,
    HERE_DOC,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    VARIABLE,
    OPTION,
    AND,
    OR,
    PARENTHESIS, // Close and open if needed
} t_token_type;

typedef struct s_token {
    int type;
    char * value;
} t_token;

// Build_lists.c
t_double_link_list ** fill_tokens_lists(char ** multiline, char *** tokens, t_double_link_list ** tokens_lists);
t_double_link_list ** init_tokens_lists (char ** multiline, char *** tokens, t_double_link_list ** tokens_lists);
t_double_link_list ** create_tokens_lists(char ** multiline);

// Tokenizer.c
t_double_link_list ** tokenizer(void);

// Free.c
void dl_free_list(t_double_link_list * tokens_list);
void free_all(char ** multiline, t_double_link_list ** tokens_list, char *** tokens);
void free_previous_tokens(size_t i, char *** tokens);

// Utils.c
void print_tokens_list(t_double_link_list ** tokens_lists);

#endif
