#include "./../../Builtins/builtins.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int pid;
	t_mylist *env_list;

	pid = fork();
	if (pid == 0)
	{
		env_list = ft_env(env);
		if (!(ft_cd(av[1], env_list)))
			system("pwd");
			// ft_pwd();
			// put_envc(env_list);
	}
	wait(NULL);

	return (0);
}


