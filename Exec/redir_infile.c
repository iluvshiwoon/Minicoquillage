#include "exec.h"

int	is_infile(char *infile)
{
	if (!ft_strncmp(infile, "<", 1))
		return (1);
	return (0);
}


char	*infile_name(char **cmds, int position)
{
	int	i;

	i = position;
	while (cmds[i][0] != '|' && cmds[i][0])
	{
		if (is_infile(cmds[i]))
			return (cmds[i + 1]);
		i++;
	}

	return (NULL);
}

void	tube_in(t_format format, int position)
{
	int		in;
	int		i;

	i = position;
	while (format.cmds[i][0] != '|' && format.cmds[i])
	{
		if (infile_name(format.cmds, i))
		{
			close(format.tube[0]);
			in = open(infile_name(format.cmds, position), O_RDONLY);
			dup2(in, STDIN_FILENO);
			close(in);
			return ;
		}
	}
	close(format.tube[0]);
	dup2(format.tube[1], STDIN_FILENO);
	close(format.tube[1]);
}
