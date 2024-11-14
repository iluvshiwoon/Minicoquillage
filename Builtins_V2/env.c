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
		write(2, "Environnement empty\n", 20);
		return (NULL);
	}
	envc = malloc(sizeof(t_mylist *));
	envc = fill_envc(env, envc);
	return (*envc);
}

void	ft_print_envc(char **env)
{
	char	**envc;

	envc = env;
	while (*envc)
	{
		write(1, *envc, ft_strlen(*envc));
		write(1, "\n", 1);
		envc++;
	}
}

int	mini_env(char **env)
{
	size_t	len;
	char	**envc;
	int	i;

	if (env == NULL || *env == NULL)
	{
		write(2, "Environnement empty\n", 20);
		return (1);
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
	ft_print_envc(envc);
	return (0);
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


// int main(int ac, char **av, char **env)
// {
// 	// t_mylist	*envc;
// 	// char		**envp;

// 	// (void )		ac;
// 	// (void )		av;
// 	// envc = ft_env(env);
// 	// envp = env_to_tab(envc);
// 	// while (*envp)
// 	// {
// 	// 	ft_putstr_fd(*envp, 1);
// 	// 	ft_putstr_fd("\n", 1);
// 	// 	envp++;
// 	// }
// 	// return (0);
// 	return ( mini_env(env));
// }


// static size_t	len_tab(char **env)
// {
// 	size_t	i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	return (i);
// }


// int	get_env(char **env, char *var)
// {
// 	int		i;
// 	int		len;
// 	char	*tmp;

// 	len = 0;
// 	i = 0;
// 	len = ft_strlen(var);
// 	while (env[i])
// 	{
// 		tmp = ft_substr(env[i], 0, len);
// 		if (!ft_strncmp(tmp, var, len))
// 			if (env[i][len] == '=')
// 				return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	put_env(char **env)
// {
// 	size_t	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		ft_putstr_fd(env[i], 1);
// 		ft_putchar_fd('\n', 1);
// 		i++;
// 	}
// }

// char	**ft_env(char **env)
// {
// 	char	**cpy_env;
// 	size_t	len;
// 	int		i;

// 	i = 0;
// 	len = len_tab(env);
// 	cpy_env = (char **)malloc((len + 1) * sizeof(char *));
// 	if (!cpy_env)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		cpy_env[i] = ft_strdup((const char *)env[i]);
// 		i++;
// 	}
// 	cpy_env[i] = NULL;
// 	return (cpy_env);
// }

