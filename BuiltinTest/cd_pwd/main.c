#include "./../../Builtins/builtins.h"
 #include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (!ft_cd(av[1], ft_env(env)))
			ft_pwd();
		else
			printf("Error Path\n");
	}
	wait(NULL);
	return (0);
}
