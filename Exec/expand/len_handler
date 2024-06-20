#include "expand.h"

int	nb_dollar_sign(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			count++;
		i++;
	}
	return (count);
}

size_t	ecxessif_len(char *ecxes)
{
	size_t c;

	c = 0;
	while (ecxes[c] != 32 && !(ecxes[c] >= 9 && ecxes[c] <= 13) && ecxes[c] != 0)
		c++;
	return (c);
}

size_t	count_len(char *cmd)
{
	size_t	i;
	size_t	l;

	l = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			l = l + ecxessif_len(&cmd[i]);
		i++;
	}
	return (i - l);
}

size_t count_sup(char **variables)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (variables[i])
	{
		len = len + ft_strlen(variables[i]);
		i++;
	}
	return (len);
}
