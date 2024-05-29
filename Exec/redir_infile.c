#include "exec.h"

int is_infile(char *infile)
{
	if (!ft_strcmp(infile, "<"))
		return (1);
	return (0);
}


/*
*operator is the current token
*file is the next token
*/
int	redirect(char *operator, char *file)
{
	int fd;
	if (is_infile(operator))
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			exit(20);
		dup2(fd, STDIN_FILENO);
	}
}
