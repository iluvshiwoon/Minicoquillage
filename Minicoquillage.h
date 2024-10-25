#ifndef MINICOQUILLAGE_H
# define MINICOQUILLAGE_H
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "42_MyLibC/mylibc.h"
# include "Utils/Utils.h"
# include "Tokenizer/Tokenizer.h"
# include "Parser/Parser.h"
# include "Exec/exec.h"

enum e_mode {
    INTERACTIVE,
    TOKENIZER,
    PARSER,
};

#ifndef MODE
# define MODE INTERACTIVE
#endif
#endif


