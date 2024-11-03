#include "./../../Builtins/builtins.h"
#include <sys/wait.h>
#include <errno.h>


int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) env;
	// ft_echo(av[1], ft_atoi(av[2]));
	ft_echo(av[1], 0);
	return (0);
}
