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

