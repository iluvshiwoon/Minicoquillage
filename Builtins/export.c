#include "./builtins.h"

int	has_character(char *var, char c)
{
	char	*cpy;

	cpy = var;
	while (*cpy)
	{
		if (*cpy == c)
			return (1);
		cpy++;
	}
	return (0);
}

int	isformatted(char *var, char *subchar)
{
	int i;

	i = 0;
	if (!var)
		return (1);
	if (!has_character(var, '='))
		return (0);
	while (*var)
	{
		if (ft_isalpha(*var) || ft_isdigit(*var) || *var == '=')
		{
			subchar[1] = subchar[1] + 1;
			var++;
		}
		else
		{
			subchar[1] = subchar[1] + 1;
			subchar[0] = subchar[1];
			var++;
		}
	}
	return (1);
}

void	add_to_env(char **env, char *variable)
{
	char	**cpy;

	cpy = env;
	while (*cpy)
		cpy++;
	*cpy = ft_strdup(variable);
	cpy++;
	*cpy = NULL;
}

void	ft_export(char **env, char *variable)
{
	char	subchar[2];
	char	*var;

	subchar[0] = 0;
	subchar[1] = 0;
	if (isformatted(variable, subchar))
	{
		var = ft_substr(variable, subchar[0], subchar[1] - subchar[0]);
		add_to_env(env, var);
	}
}

