
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



char	**env_to_tab(t_mylist *env)
{
	int count = 0;
	t_mylist *current = env;

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
	for (int i = 0; i < count; i++)
	{
		// Créer une chaîne formatée "var=val"
		tab[i] = malloc(strlen((char *)current->var) + strlen((char *)current->val) + 2); // +2 pour '=' et '\0'
		if (tab[i] == NULL)
		{
			// Libérer la mémoire en cas d'échec
			for (int j = 0; j < i; j++)
				free(tab[j]);
			free(tab);
			return NULL;
		}
		sprintf(tab[i], "%s=%s", (char *)current->var, (char *)current->val);
		current = current->next;
	}

	// Terminer le tableau avec un pointeur NULL
	tab[count] = NULL;

	return tab;
}
