#include "./../../builtins.h"

int	main(int ac, char **av, char **env)
{

	ft_cd(av[1], ft_env(env));
	ft_pwd();
	return (0);
}
