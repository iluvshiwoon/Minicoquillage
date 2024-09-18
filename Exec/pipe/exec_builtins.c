#include "pipex.h"

int	is_builtin(t_double_link_node **node)
{
	int					i;
	t_double_link_node	*nodecpy;
	char *b[7] = {"env", "pwd", "unset", "export", "cd", "echo", "exit"};

	i = 0;
	nodecpy = *node;
	while (i < 7)
	{
		i++;
	}
	return (0);
}

