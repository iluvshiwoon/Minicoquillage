#include "./../../Builtins/builtins.h"
#include <sys/wait.h>
#include <errno.h>

int	main(int ac, char **av, char **env)
{
	echo(av[1]);
	return (0);
}
