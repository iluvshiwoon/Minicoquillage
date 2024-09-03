#include "./builtins.h"


int	ft_separator(char *variable)
{
	int		i;
	char	*varc;

	varc = variable;
	i = 0;
	while (*variable != '=')
	{
		i++;
		varc++;
	}
	return (i);
}

int fill_envc(char **env, t_mylist	*envc)
{
	int			i;
	int			separator;
	char		**var;
	t_mylist	*cursor_var;

	i = 0;
	var = env;
	cursor_var = envc;
	while (var[i])
	{
		separator = ft_separator(var[i]);
		has_content(cursor_var, separator);
		i++;
	}
	return i;
}

t_mylist	*ft_env(char **env)
{
	t_mylist	*envc;

	envc = malloc(sizeof(t_mylist));
	if (!envc)
		return (NULL);
	fill_envc(env, envc);
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
}



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


