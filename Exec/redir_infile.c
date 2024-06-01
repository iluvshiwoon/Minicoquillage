#include "exec.h"

int is_infile(char *infile)
{
	if (!ft_strncmp(infile, "<", 1))
		return (1);
	return (0);
}


char	*infile_name(char **cmds, int position)
{
	int	i;

	i = position;
	while (cmds[i][0] != '|')
	{
		if (is_infile(cmds[i]))
			return (cmds[i + 1]);
		i++;
	}

	return (NULL);
}

char	tube_redirect(char **cmds, int position)
{
	
}
