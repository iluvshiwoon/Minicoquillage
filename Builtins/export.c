#include "./builtins.h"



int	isformatted(char *var)
{
	int egal = 0;
	int start = 0;
	int len = 0;

	if (!var)
		return (1);
	if (ft_isalpha(*var))
		var++;
	while (var)
	{
		if (ft_isalnum(*var) || var == '=')
			var++;
		else (
	}

}

void	export(char **env, char *variable)
{
	if (isformatted(variable))
		add_to_env(env, variable);
}
