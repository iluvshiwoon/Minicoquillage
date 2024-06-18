#include "./exec.h"

int	search_nb_vars(char *cmd)
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

void	add_variables(char *cursor, char **variables, int *index)
{
	char	*end;
	int		i;

	cursor = cursor++;
	end = ft_strchr(cursor, ' ');
	if (!end)
		end = ft_strchr(cursor, 0);
	i = end - cursor;
	variables[*index] = ft_substr(cursor, 0, i);
}

int	fill_var_arr(char *cmd, char **variables, int nb_vars)
{
	char	*cursor;
	int		i;

	i = 0;
	cursor = cmd;
	variables = (char **)malloc((nb_vars + 1) * sizeof(char *));
	if (!variables)
		return (0);
	while (*cursor)
	{
		if (*cursor == '$')
		{
			add_variables(cursor, variables, &i);
			i++;
		}
		cursor++;
	}
	return (1);
}

int	set_to_expand(char *cmd, char **variables)
{
	int	nb_vars;

	nb_vars = search_nb_vars(cmd);
	if (!nb_vars)
		return (0);
	else
		return (fill_var_arr(cmd, variables, nb_vars));
}

void	go_to_next(char *cmd)
{
	while (*cmd != 32 || !(*cmd >= 9 && *cmd <= 13))
		cmd = ++cmd;
}

void put_variables(char *msg, int *i, char **variables)
{
	int	k;

	k = 0;
	while (variables[0][k])
	{
		msg[*i] = variables[0][k];
		k++;
		*i = *i + 1;
	}
	free(variables[0]);
	variables = &variables[1];
}

void	is_variable(char *cmd, char *msg, int *i, char **variables)
{
	go_to_next(cmd);
	put_variables(msg, i, variables);
}

size_t	ecxessif_len(char *ecxes)
{
	size_t c;

	c = 0;
	while (ecxes[c] != 32 || !(ecxes[c] >= 9 && ecxes[c] <= 13) || ecxes[c] != 0)
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

char	*to_expand(char *cmd, char **variables)
{
	int		i;
	char	*msg;
	size_t	len;
	size_t	len_sup;

	len_sup = count_sup(variables);
	len = count_len(cmd);
	msg = (char *)ft_calloc((len + len_sup + 1), sizeof(char));
	if (!msg)
		return (NULL);
	i = 0;
	while (*cmd)
	{
		if (*cmd == '$' && cmd[-1] != '$')
			is_variable(cmd, msg, &i, variables);
		else
		{
			msg[i] = *cmd;
			i++;
			cmd++;
		}
	}
	msg[i] = 0;
	return (msg);
}

char	*expand(char **env, char *cmd)
{
	char	**v_env;
	int		i;

	v_env = NULL;
	if (!set_to_expand(cmd, v_env))
		return (cmd);
	else
	{
		v_env = switch_from_env(v_env, env); //transforme les variable par ce qui lui est associe dans env
		return (to_expand(cmd, v_env));
	}
}





// a = "o salut le monde"
// ech$a:		echo salut le monde
//
// $a exist or not
