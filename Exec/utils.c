#include "./exec.h"

int	ft_strlen2(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[i])
		return (i);
	while (tab[i])
		i++;
	return (i);
}

void	*ft_free_tab(char **s, size_t i)
{
	size_t	k;

	k = 0;
	while (k < i)
	{
		free(s[k]);
		k++;
	}
	free(s);
	return (NULL);
}

static size_t	len_tab(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**ft_env(char **env)
{
	char	**cpy_env;
	size_t	len;
	size_t	i;

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
