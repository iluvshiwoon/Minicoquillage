#ifndef MINICOQUILLAGE_H
# define MINICOQUILLAGE_H
# include "42_MyLibC/mylibc.h"
# include "Tokenizer/Tokenizer.h"
# include "Parser/Parser.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_mode {
    INTERACTIVE,
    DEBUG,
    TOKEN,
    EXPANSION,
};

#ifndef MODE
# define MODE INTERACTIVE
#endif
#endif


