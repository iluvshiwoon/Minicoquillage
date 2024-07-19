#include "format.h"

int	last_infile(t_token *infile)
{
	int	i;
	int fd;

	fd = open(infile->value, O_RDONLY);
	return fd;
}

int	last_outfile(t_token *infile)
{
	int	i;
	int fd;

	fd = open(infile->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return fd;
}
