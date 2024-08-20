#include "formatting.h"

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
		status->fdin = ft_strdup(((t_token *)file->data)->value);
		printf("handle_redir  %s %s\n", ((t_token *)file->data)->value , status->fdin);
	}
	if (!ft_strncmp(((t_token *)(*node)->data)->value, ">", 1))
		status->fdout = ft_strdup(((t_token *)file->data)->value);
}

void	fill_2(t_status *status, t_double_link_node **node, int i)
{
	char				**tab;
	int					size;
	t_double_link_node	*node2;

	node2 = *node;
	size = 0;
	tab = (char **)malloc(sizeof(char *) * (i + 1));  // faire un ft_calloc?
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

t_format *to_fill_(t_status *status, t_double_link_node *node, char **env, int i)
{
	char *my_path;

	my_path = ft_sx_path(((t_token *)node->data)->value, env);
	status->cmd->_path = my_path;
	fill_2(status, &node, i);
	//display_tab_of_cmd(status->cmd->_tab);
	status->cmd->_haspipe = -1;
	return (status->cmd);
}

t_double_link_node	*next_process(t_double_link_node **node)
{
	t_double_link_node **next_node;

	if (!node || !(*node))
		return (NULL);
	next_node = node;
	if (!(*next_node)->next)
		return (NULL);
	while ((t_token *)(*next_node)->data)
	{
		*next_node = (*next_node)->next;
		if (!(*next_node))
			break ;
		if (((t_token *)(*next_node)->data)->type == COMMAND)
		{
			printf("NN : %s\n", ((t_token *)(*next_node)->data)->value);
			return (*next_node);
		}
	}
	return (NULL);
}

int	nb_of_cmd(t_status *status, t_double_link_node *node)
{
	t_double_link_node	*nodecpy;
	int					i;

	if (!node)
		return (0);
	if (((t_token *)node->data)->type == COMMAND)
		i = 1;
	else
		i = 0;
	nodecpy = node;
	while (status->next_process)
	{
			i++;
			status->next_process = next_process(&status->next_process);
	}
	return (i);
}

t_status	*init_status(t_double_link_node *node, t_status *status, char **env)
{
	int	i;

	if (!node)
		return (NULL);
	i = nb_token_for_cmd(&node);
	status->cmd = malloc(sizeof(t_format));
	status->cmd->_tab = (char **)malloc((i + 1) * sizeof(char *));
	status->envp = (char **)malloc(100 * sizeof(char *));
	status->envp = env;
	status->fdout = NULL;
	status->fdin = NULL;
	to_fill_(status, node, env, i);
	status->next_process = next_process(&node);
	if (!status->next_process)
		status->cmd->_haspipe = 0;
	else
		status->cmd->_haspipe = 1;
	status->nb_cmd = nb_of_cmd(status, node);
	status->current_cmd = status->nb_cmd;
	if (status->next_process)
		printf("NEXT: %s\n", ((t_token *)(status->next_process->data))->value);
	return (status);
}


