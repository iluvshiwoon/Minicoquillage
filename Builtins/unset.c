#include "./builtins.h"

char	*get_var_env(char *var, char **env)
{
	if (!env || !*env)
		return (NULL);
	while (env || *env)
	{
		if (ft_strnstr(*env, var, ft_strlen(var) + 1))
			return (*env);
		else
			++env;
	}
	return (NULL);
}

int is_present(char **env, char *variable)
{
	if(getenv(variable))
		return (1);
	return (0);
}

void	remove_var(char **env, char *variable)
{
	int	i;
	int j;

	i = 0;
	char	*to_remove = get_var_env(variable, env);
	while (env[i] != to_remove)
		i++;
	j = i + 1;
	while (env[j])
	{
		env[i] == env[j];
		i++;
		j++;
	}
	env[i] == NULL;
}

void	ft_unset(char **env, char *variable)
{
	if (is_present(env, variable))
		remove_var(env, variable);
}


int	main(int ac, char **av, char **environment)
{
	char **env = ft_env(environment);

	unset(env, "toto");

}
