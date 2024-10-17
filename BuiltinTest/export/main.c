#include "./../../Builtins/builtins.h"
#include <fcntl.h>

int	main(int ac, char **av, char **env)
{
	t_mylist	*envc;
	int fd;
	char *line;

	(void )		ac;
	(void )		av;
	envc = ft_env(env);
	fd = open("variables.txt",  O_RDWR);
	if (fd == -1)
	{
		printf("Error in opening file\n");
		return (1);
	}
	while ((line = get_next_line(fd)) > 0)
	{
		ft_export(envc, line);
	}
	put_envc(envc);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_mylist	*envc;
// 	int i;

// 	i = 1;
// 	(void )		ac;
// 	(void )		av;
// 	envc = ft_env(env);
// 	while(av[i])
// 	{
// 		ft_export(envc, av[i]);
// 		i++;
// 	}
// 	put_envc(envc);
// 	return (0);
// }
