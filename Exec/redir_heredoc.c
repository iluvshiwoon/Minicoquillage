#include "exec.h"

int is_infile(char *infile)
{
	if (!ft_strcmp(infile, "<"))
		return (1);
	return (0);
}


char	*infile_name(char **context, int position)
{
	int	i;

	i = position;
	while (context[i][0] != '|')
	{
		if (is_infile(context[i]))
			return (context[i + 1]);
		i++;
	}
	return (NULL);
}
