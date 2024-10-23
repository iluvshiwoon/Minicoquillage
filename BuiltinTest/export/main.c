#include "./../../Builtins/builtins.h"
#include <fcntl.h>


int	main(int ac, char **av, char **env)
{
	t_mylist	*envc;
	int fd;
	char *line;
	int status;

	(void )		ac;
	(void )		av;
	status = 0;
	envc = ft_env(env);
	fd = open("variables.txt",  O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("Error in opening file\n");
		return (1);
	}
	while ((line = (get_next_line(fd)) ) > 0)
	{
		status += ft_export(envc, line);
		free(line);
		line = NULL;
	}
	put_envc(envc);
	return (status);
}
