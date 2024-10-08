#include "./../../builtins.h"

int	main(int ac, char **av, char **env)
{
	t_mylist	*envc;

	(void )		ac;
	(void )		av;
	envc = ft_env(env);
	put_envc(envc);
	return (0);
}
