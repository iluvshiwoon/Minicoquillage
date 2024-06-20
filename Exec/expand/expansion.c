#include "./expand.h"

void	put_variables(char *msg, int *i, char **variables)
{

}

void	is_variable()
{

}

char	*is_var_exist(char *v_env, char **env)
{
	char	*pattern;
	int		i;

	i = 0;
	pattern = ft_strjoin((const char*)v_env, "=");
	while (env[i])
	{
		if (ft_strnstr(env[i], pattern, ft_strlen(pattern) - 1))
			return (env[i]);
		else
			i++;
	}
	return (NULL);
}

// a = "o salut le monde"
// ech$a:		echo salut le monde
//
// $a exist or not

