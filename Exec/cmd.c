#include "exec.h"

char	*path_of_cmd(char **env, char *cmd)
{
	char *path;
	path = pss_permission(env, cmd);
	return (path);
}

int among_cmd(char c)
{
	int i;
	//forbidden instead token's type to check if value is among current cmd
	char *forbidden = "|<>&()";
	i = 0;
	while (forbidden[i])
	{
		if (forbidden[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	insert_full_cmd(char **f_cmd, char **tokens, int i, int size_cmd)
{
	int	k;
	int	j ;

	j = i;
	k = 0;
	while (k < size_cmd)
	{

		f_cmd[k] = ft_strdup(tokens[j]);
		k++;
		j++;
	}
	f_cmd[k] = NULL;
}

char	**ft_cmd(char **to_exec, int i, int *j, char **tokens)
{
	int		size_cmd;

	size_cmd = 0;
	while (among_cmd(tokens[i][0]))
	{
		size_cmd++;
		i++;
	}
	to_exec = (char **)malloc((1 + sizeof(char)) * size_cmd);
	if (!to_exec)
		return (NULL);
	insert_full_cmd(to_exec, tokens, *j, size_cmd);
	*j = i;
	return (to_exec);
}
