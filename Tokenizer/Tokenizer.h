#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type {
    COMMAND, // relative or absolute if needed
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

#endif
