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

void	tube_out(t_format format, int position)
{
	char	*specials = "|<>&()";
	int		out;

	if (!outfile_name(format.cmds, position))
	{
		close(format.tube[1]);
		dup2(format.tube[0], STDOUT_FILENO);
		close(format.tube[0]);
	}
	else
	{
		printf("ici");
		close(format.tube[0]);
		out = open(outfile_name(format.cmds, position), O_CREAT | O_WRONLY);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
