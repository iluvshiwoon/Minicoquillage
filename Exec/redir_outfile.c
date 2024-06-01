#include "exec.h"

int is_outfile(char *infile)
{
	if (!ft_strncmp(infile, ">", 1))
		return (1);
	return (0);
}


char	*outfile_name(char **cmds, int position)
{
	int	i;

	i = position;
	while (cmds[i][0] != '|')
	{
		if (is_outfile(cmds[i]))
			return (cmds[i + 1]);
		i++;
	}
	return (NULL);
}
