
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

char	*store_env(char *tab, char *var, char *val)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(var, "=");
	tmp2 = ft_strjoin(tmp, val);
	tab = ft_strjoin(tmp2, "\0");
	free(tmp);
	free(tmp2);
	return (tab);
}



/**
 * env_to_tab - convert a linked list of environment variables into a table of strings
 * @env: linked list of environment variables
 */
char	**env_to_tab(t_mylist *env)
{
	int count;
	int i;
	int j;
	t_mylist *current = env;

	i = 0;
	j = 0;
	count = 0;
	// Compter le nombre d'éléments dans la liste
	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	// Allouer de la mémoire pour le tableau de chaînes de caractères
	char **tab = malloc((count + 1) * sizeof(char *));
	if (tab == NULL)
		return NULL;

	// Remplir le tableau avec les éléments de la liste
	current = env;
	while (i < count)
	{
		// Créer une chaîne formatée "var=val"
		tab[i] = malloc(strlen((char *)current->var) + strlen((char *)current->val) + 2); // +2 pour '=' et '\0'
		if (tab[i] == NULL)
		{
			// Libérer la mémoire en cas d'échec
			while (j < i)
				free(tab[j++]);
			free(tab);
			return NULL;
		}
		// sprintf(tab[i], "%s=%s", (char *)current->var, (char *)current->val);
		tab[i] = store_env(tab[i], (char *)current->var, (char *)current->val);
		current = current->next;
		i++;
	}
	// Terminer le tableau avec un pointeur NULL
	tab[count] = NULL;

	return tab;
}



// int	ft_strlen2(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!tab || !tab[i])
// 		return (i);
// 	while (tab[i])
// 		i++;
// 	return (i);
// }

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

size_t	ft_tab2len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	*ft_free_envl(t_mylist *s)
{
	t_mylist	*k;

	while (s)
	{
		free(s->val);
		free(s->var);
		k = s;
		s = s->next;
		free(k);
	}
	return (NULL);
}

