#include "./pipex.h"


void	error_cmd(char *err, char *cmd)
{
	ft_putstr_fd("minicoquillage:", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

