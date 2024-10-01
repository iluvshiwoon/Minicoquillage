#include "./expand.h"

char	*var_exist(char *var, char **env)
{
	char	*pattern;
	int		i;

	i = 0;
	pattern = ft_strjoin((const char*)(var), "=");
	while (env[i])
	{
		if (ft_strnstr(env[i], pattern, ft_strlen(pattern)))
			return (env[i]);
		else
			i++;
	}
	return (NULL);
}

char	*is_variable(char *variable, char **env)
{
	int		i;
	char	*space;
	char	*tmp;

	i = 0;
	tmp = variable;
	while (*tmp == ' ')
		tmp++;
	space = ft_substr(variable, 0, (tmp - variable));
	tmp = var_exist(tmp, env);
	if (!tmp)
		return (free(tmp), free(space), variable);
	else
		while (*tmp != '=')
			tmp++;
	tmp = ft_strjoin(space, ++tmp);
	return (tmp);
}


// a = "o salut le monde"
// ech$a:		echo salut le monde
//
// $a exist or not

