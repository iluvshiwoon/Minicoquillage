#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../Minicoquillage.h"

typedef enum e_token_type {
    COMMAND, // relative or absolute if needed
    ARG,
    // ARG_LITTERAL,
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

typedef struct s_status {
    int index;
    int exist;
} t_status;
 
typedef struct s_matching {
    t_status open;    
    t_status close;
} t_matching;

// Build_lists.c
t_double_link_list ** fill_tokens_lists(char ** multiline, char *** tokens, t_double_link_list ** tokens_lists);
t_double_link_list ** init_tokens_lists (char ** multiline, char *** tokens, t_double_link_list ** tokens_lists);
t_double_link_list ** create_tokens_lists(char ** multiline);

// Tokenizer.c
t_double_link_list ** tokenizer(void);

// Free.c
void dl_free_list(t_double_link_list * tokens_list);
// void free_all(char ** multiline, t_double_link_list ** tokens_list);
void free_all(char ** multiline, t_double_link_list ** tokens_list, char *** tokens);
void free_previous_tokens(size_t i, char *** tokens);

// Prompt.c
char * build_prompt();
char * last_ocur (char * string , char c);

// Utils.c
void print_tokens_list(t_double_link_list ** tokens_lists);
void print_list(t_double_link_list * tokens_lists);

// try 
char * expand(char * line, size_t index, size_t j);
size_t expand_double_quote(char * line, size_t i, size_t j, t_double_link_list * list);
t_double_link_list * create_tokens(char * line);

#endif
