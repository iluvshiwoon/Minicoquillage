#include "./builtins.h"

int	ft_separator(char *variable)
{
	int		i;
	char	*varc;

	varc = variable;
	i = 0;
	while (*varc != '=')
	{
		i++;
		varc++;
	}
	return (i);
}

t_mylist	*fill_content(char *str, int sep)
{
	t_mylist	*node;

	node = malloc(sizeof(t_mylist));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->var = ft_substr(str, 0, sep);
	node->val = ft_substr(str, sep + 1, ft_strlen(str) - sep);
	return (node);
}

t_mylist	**fill_envc(char **env, t_mylist **content)
{
	t_mylist	*node_var;
	t_mylist	*node_first;
	char		**var;
	int			separator;
	int			i;

	i = 0;
	var = env;
	if (i == 0)
	{
		separator = ft_separator(var[i]);
		node_first = fill_content(var[i], separator);
		*content = node_first;
		i++;
	}
	while (var[i])
	{
		separator = ft_separator(var[i]);
		node_var = fill_content(var[i], separator);
		node_first->next = node_var;
		node_first = node_first->next;
		i++;
	}
	return (content);
}


/**
 * ft_env: transform the environment variables into a linked list t_mylist
 * @env: the environment variables from the main
 * @return: the linked list t_mylist
 * To free:
 * 				- free all var from the linked list
 *				- free all val from the linked list
 * 				- then free the linked list after using it
 */
t_mylist	*ft_env(char **env)
{
	t_mylist	**envc;
	t_mylist	*content;

	if (env == NULL || *env == NULL)
	{
		ft_putstr_fd("Environnement empty\n", 2);
		return (NULL);
	}
	envc = malloc(sizeof(t_mylist *));
	envc = fill_envc(env, envc);
	return (*envc);
}


char	**mini_env(char **env)
{
	size_t	len;
	char	**envc;
	int	i;

	if (env == NULL || *env == NULL)
	{
		ft_putstr_fd("Environnement empty\n", 2);
		return (NULL);
	}
	i = 0;
	len = ft_tab2len(env);
	envc = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		envc[i] = ft_strdup((const char *)env[i]);
		i++;
	}
	envc[i] = NULL;
	return (envc);
}

void	put_envc(t_mylist *env)
{
	t_mylist	*cursor;

	cursor = env;
	while (cursor)
	{
		ft_putstr_fd(cursor->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(cursor->val, 1);
		ft_putstr_fd("\n", 1);
		cursor = cursor->next;
	}
}
