#include "./../../Builtins/builtins.h"

// char*	file_to_env(char *file)
// {
// 	int		fd;
// 	char	*line;
// 	char	*env;
// 	int		i;

// 	i = 0;
// 	env = malloc(1000);
// 	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
// 	while ((line = get_next_line(fd)) > 0)
// 	{
// 		ft_strlcpy(&env[i], line, ft_strlen(line));
// 		i += ft_strlen(line);
// 		env[i] = '\n';
// 		i++;
// 	}
// 	env[i] = '\0';
// 	return (env);
// }



int	main(int ac, char **av, char **env)
{
	t_mylist	*envc;
	int i;

	i = 1;
	(void )		ac;
	envc = ft_env(env);
	while (av[i])
	{
		ft_unset(envc, av[i]);
		i++;
	}
	put_envc(envc);
	return (0);
}
