#include "formatting.h"

size_t	count_var(t_mylist *env)
{
	size_t		len;
	t_mylist	*envc;

	len = 0;
	envc = env;
	while (envc)
	{
		len++;
		//if (envc->next)
		envc = envc->next;
	}
	return (len);
}

void	env_to_tab_2(t_mylist *env, char **envtab, size_t nb_var)
{
	size_t		i;
	size_t		a;
	size_t		b;
	t_mylist	*envc;

	envc = env;
	i = 0;
	while (envtab[i])
	{
		a = ft_strlen(env->var);
		ft_strlcat(envtab[i], "=", a + 2);
		envc = env->next;
		i++;
	}
	envc = env;
	i = 0;
	while (envtab[i])
	{
		a = ft_strlen(env->var);
		b = ft_strlen(env->val);
		ft_strlcat(envtab[i], "=", a + b + 1);
		envc = env->next;
		i++;
	}
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

// char	**env_to_tab(t_mylist *env)
// {
// 	// t_mylist	*envc;
// 	// char		**envtab;
// 	// size_t		nb_var;
// 	// int			i;

// 	// i = -1;
// 	// envc = env;
// 	// nb_var = count_var(env);
// 	// envtab = malloc(nb_var * sizeof(char *));
// 	// if (!envtab)
// 	// 	return (NULL);
// 	// while (envtab[++i])
// 	// 	envtab[i] = ft_strdup("");
// 	// while (envc)
// 	// {
// 	// 	envtab[i] = ft_strdup(envc->var);
// 	// 	envc = envc->next;
// 	// }
// 	// envtab[i] = NULL;
// 	// env_to_tab_2(env, envtab, nb_var);
// 	// return (envtab);



// }

int	expression(t_token *token)
{
	t_token_type limit_expressio[] = {OR, AND, OPEN_PARENTHESIS, CLOSE_PARENTHESIS, PIPE};
	int i;

	i = 0;
	while (i < 5)
	{
		if (token->type == limit_expressio[i])
			return (0);
		i++;
	}
	return (1);
}


int	nb_token_for_cmd(t_double_link_node **node)
{
	t_double_link_node	*node_cpy;
	t_token_type limit_expressio[] = {OR, AND, OPEN_PARENTHESIS, CLOSE_PARENTHESIS, PIPE};
	int 				nb;
	int					f;

	nb = 0;
	f = 0;
	node_cpy = *node;
	while (node_cpy && expression((t_token *)node_cpy->data))
	{
		nb++;

		node_cpy = node_cpy->next;
		if (node_cpy)
		{
			if (f > 0 && (((t_token *)node_cpy->data)->type == COMMAND))
				return (nb);
			if (((t_token *)node_cpy->data)->type == COMMAND)
				f++;
		}
	}
	return (nb);
}

void	handle_redirection(t_status *status, t_double_link_node **node)
{
	int					flagin;
	int					flagout;
	t_double_link_node	*file;

	flagin = O_RDONLY;
	flagout = O_CREAT | O_WRONLY | O_TRUNC;
	file = (*node)->next;
	if (!ft_strncmp(((t_token *)(*node)->data)->value, "<", 1))
	{
		status->cmd->fdin_ = ft_strdup(((t_token *)file->data)->value);
		// printf("handle_redir  %s %s\n", status->cmd->fdin_, status->fdin);
	}
	if (!ft_strncmp(((t_token *)(*node)->data)->value, ">", 1))
	{
		status->cmd->fdout_ = ft_strdup(((t_token *)file->data)->value);
		// printf("handle_redir  %s %s\n", status->cmd->fdout_, status->fdout);

	}
}

void	fill_2(t_status *status, t_double_link_node **node, int i)
{
	char				**tab;
	int					size;
	t_double_link_node	*node2;

	node2 = *node;
	size = 0;
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	while (size < i && node2)
	{
		if (((t_token *)node2->data)->type == REDIRECTION)
		{
			handle_redirection(status, &node2);
			node2 = (node2->next);
		}
		else if ((((t_token *)node2->data)->type == COMMAND) ||
			(((t_token *)node2->data)->type == ARG) || //modifier arg des redirection de e_token_type?
			(((t_token *)node2->data)->type == OPTION))
		{
			tab[size] = ft_strdup(((t_token *)node2->data)->value);
			size++;
		}
		node2 = node2->next;
	}
	tab[size] = NULL;
	status->cmd->_tab = tab;
}

void	display_tab_of_cmd(char **tab)
{
	char	**tabcpy;

	tabcpy = tab;
	while (*tabcpy)
	{
		printf("VALUE: %s\n", *tabcpy);
		tabcpy++;
	}
}

t_format *to_fill_(t_status *status, t_double_link_node *node, t_mylist *env, int i)
{
	char		*my_path;
	t_mylist	*envc;

	envc = env;
	my_path = ft_sx_path(((t_token *)node->data)->value, envc);
	status->cmd->_path = my_path;
	fill_2(status, &node, i);
	//display_tab_of_cmd(status->cmd->_tab);
	// status->cmd->_haspipe = -1;
	return (status->cmd);
}

t_double_link_node	*next_process(t_double_link_node **node)
{
	t_double_link_node *next_node;

	if (!node || !(*node))
		return (NULL);
	next_node = *node;
	if (!(next_node)->next || !(next_node))
		return (NULL);
	while ((t_token *)(next_node)->data)
	// while ((t_token *)((next_node->next))->data)
	{
		next_node = (next_node)->next;
		if (!(next_node))
			break ;
		if (((t_token *)(next_node)->data)->type == COMMAND)
		{
			//printf("NC : %s\n", ((t_token *)(next_node)->data)->value);
			return (next_node);
		}
	}
	return (NULL);
}

int	nb_of_cmd(t_status *status, t_double_link_node *node)
{
	int					i;

	if (!node)
		return (0);
	if (((t_token *)node->data)->type == COMMAND)
		i = 1;
	else
		i = 0;
	while (status->next_process)
	{
			i++;
			status->next_process = next_process(&status->next_process);
	}
	status->next_process = next_process(&node);
	return (i);
}

t_status	*init_status(t_double_link_node *node, t_status *status, t_mylist *env)
{
	int			i;
	t_mylist	*envc;

	// printf("env->val : %s\n", (char *)env->val);
	if (!node)
		return (NULL);
	// if (run_built(node, &env))
	// {
		envc = env;
		i = nb_token_for_cmd(&node);
		status->cmd = malloc(sizeof(t_format));
		status->cmd->_tab = (char **)malloc((i + 1) * sizeof(char *));
		status->envp = malloc(sizeof(t_mylist));
		status->envp = envc;
		status->cmd->fdout_ = NULL;
		status->cmd->fdin_ = NULL;
		status->envc = env_to_tab(env);
		to_fill_(status, node, envc, i);
		status->next_process = next_process(&node);
		status->nb_cmd = nb_of_cmd(status, node);
		status->current_cmd = status->nb_cmd;
	// }
	return (status);
}


