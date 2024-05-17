#include "./builtins.h"


static size_t	len_tab(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}


void	put_env(char **env)
{
	size_t	i;

	i = 0;
	while(env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**ft_env(char **env)
{
	char	**cpy_env;
	size_t	len;
	int		i;

	i = 0;
	len = len_tab(env);
	cpy_env = (char **)malloc((len + 1) * sizeof(char));
	if (!cpy_env)
		return (NULL);
	while (i < len)
	{
		cpy_env[i] = ft_strdup((const char *)env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
}
