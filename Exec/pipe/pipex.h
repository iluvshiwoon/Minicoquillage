#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include "../../42_MyLibC/mylibc.h"
# include "../../Builtins/builtins.h"
# include "../../Tokenizer/Tokenizer.h"
# include "../exec.h"

# define ERR_NOT_FOUND ": command not found:"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		tube[2];
	char	**env;
	char	**path;
	char	**cmds[3];
}			t_pipex;



// char	*check_token_is_cmd(t_token *token, char **env);
void	error_cmd(char *err, char *cmd);
#endif

