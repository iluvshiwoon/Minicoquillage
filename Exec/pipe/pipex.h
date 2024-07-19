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
# include "../../Minicoquillage.h"

# define ERR_NOT_FOUND ": command not found:"




// char	*check_token_is_cmd(t_token *token, char **env);
void	error_cmd(char *err, char *cmd);
#endif

