#include "./../../builtins.h"


int	main(int ac, char **av, char **env)
{
	t_mylist	*envc;
	int i;

	i = 1;
	(void )		ac;
	(void )		av;
	envc = ft_env(env);
	// while(av[i])
	// {
		ft_export(envc, av[i]);
		// i++;
	// }
	put_envc(envc);
	return (0);
}
