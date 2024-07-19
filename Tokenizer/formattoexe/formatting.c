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
	while (expression((t_token *)node_cpy->data))
	{
		nb++;

		node_cpy = node_cpy->next;
		if (f > 0 && (((t_token *)node_cpy->data )->type == COMMAND))
			return (nb);
		if (((t_token *)node_cpy->data )->type == COMMAND)
			f++;
	}
	return (nb);
}

// t_status	*init_status(t_double_link_list *list, t_status *status)
// {
// 	if (!list)
// 		return (NULL);
// 	status->formatted_cmd = NULL;
// 	status->next_node_valide = list->first_node;
// 	return (status);
// }

// t_status	*fill_status(t_double_link_node *node, t_status *status)
// {
// 	int		nb;
// 	t_token	*data;

// 	if (!node)
// 		return (NULL);
// 	data = (t_token *)node->data;
// 	if (!data)
// 		return (NULL);
// 	nb = nb_token_for_cmd(&node);
// 	status->formatted_cmd = formatting(status);
// 	status->next_node_valide = to_next_cmd(node);
// 	return (status);
// }


t_format *to_fill_(t_status *status, t_double_link_node *node, char **env)
{
	status->cmd->_path = ft_sx_path(((t_token *)node->data)->value, env);
	fill_2()
}

t_status	*init_status(t_double_link_node *node, t_status *status, char **env)
{
	if (!node)
		return (NULL);
	status->envp =
	status->next_process = node;
	status->cmd = to_fill_(status, node, env);
	return (status);
}
