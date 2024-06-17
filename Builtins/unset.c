#include "./builtins.h"

int	is_present(char **env, char *variable)
{
	if (get_env(env, variable))
		return (1);
	return (0);
}

void	remove_var(char **env, char *variable)
{
	int	i;
	int j;

	i = 0;
	char *to_remove = get_var_env(variable, env);
	ft_printf("%s\n", to_remove);
	while (ft_strncmp(env[i], to_remove, ft_strlen(to_remove)))
		i++;
	j = i + 1;
	while (env[j])
	{
		env[i] = env[j];
		i++;
		j++;
	}
	env[i] = NULL;
}

void	ft_unset(char **env, char *variable)
{
	if (is_present(env, variable))
		remove_var(env, variable);
}

