#include "expand.h"

char	*expand(char **env, char *str)
{
	char	*expanded;
	t_list	*piece_of_str;

	piece_of_str = NULL;
	store_str_to_expand(&piece_of_str, str);
	if (!nb_dollar_sign(str))
		simple_expand(expanded, piece_of_str);
	else
	{
		complete_infos_to(piece_of_str);
		complexe_expand(expanded, piece_of_str);
	}
	return (expanded);
}

int	main(int ac, char **av, char **env)
{
	char	**copyenv;
	char	*expander;

	(void)ac;
	(void)av;
	copyenv = ft_env(env);
	expander = expand(copyenv, "un $test bd");
	ft_printf("%s\n", expander);
	return (0);
}
