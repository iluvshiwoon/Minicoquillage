#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include "../42_MyLibC/mylibc.h"

typedef struct s_format
{
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	int		here_doc;


}			t_format;

#endif
