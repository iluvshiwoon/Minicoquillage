#ifndef MINICOQUILLAGE_H
# define MINICOQUILLAGE_H
# include <stdio.h>
# include <termios.h>
#include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "42_MyLibC/mylibc.h"
# include "Utils/Utils.h"
# include "Tokenizer/Tokenizer.h"
# include "Parser/Parser.h"
# include "Exec/exec.h"
# include "Expand/expand.h"
# include "glob/glob.h"
# include "Builtins_V2/builtin.h"

void _close(int fd);

extern int g_signal;
enum e_mode {
    INTERACTIVE,
    TEST
};

#ifndef MODE
# define MODE INTERACTIVE
#endif
#endif


