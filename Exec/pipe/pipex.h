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
# include "../../Tokenizer/formattoexe/formatting.h"

# define ERR_NOT_FOUND ": command not found:"

t_status	*sx_process_next_2(t_status *mystatus);
void		execut(t_status *mystatus);
void		execute_simple_command_2(t_status *mystatus);
void		execute_with_pipes_2(t_status *mystatus);
void		exec_multi(t_status *mystatus);
void		last_command(t_status *status);



#endif

