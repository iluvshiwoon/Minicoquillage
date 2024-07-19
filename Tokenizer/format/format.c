#include "format.h"


// int	expression(t_token *token)
// {
// 	t_token_type limit_expressio[] = {OR, AND, OPEN_PARENTHESIS, CLOSE_PARENTHESIS, PIPE};
// 	int i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		if (token->type == limit_expressio[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


int exp_size(t_double_link_list **list, t_double_link_node **node_o)
{
	t_double_link_node	*node;
	int					i;

	i = 0;
	node = (*node_o);
	// node = (*list)->first_node;
	while (node != NULL && node->data != NULL && expression((t_token *)node->data) == 1)
	{
		node  = node->next;
		i++;
	}
	printf("format.c - expression size :%d\n", i);
	return (i);
}

char	**tab_cmd(t_format_cmd *cmd)
{
	int 	s;
	int		i;
	int		j;
	char 	**tab;

	i = 0;
	j = 0;
	s = size_cmd(cmd);
	tab = (char **)malloc((s + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[i++] = cmd->cmd_name->value;
	while (cmd->option[j])
		tab[i++] = cmd->option[j++]->value;
	j = 0;
	while (cmd->argument[j])
		tab[i++] = cmd->argument[j++]->value;
	tab[i] = NULL;

	printf("Nombre d element cmd:%d\n", i);
	return (tab);
}

t_format_cmd	*format_array(t_double_link_list **list_o, t_double_link_node **node_o)
{
	t_double_link_list	*list;
	t_double_link_node	*node;
	t_format_cmd		*cmd;
	int					size;

	list = *list_o;
	node = *node_o;
	cmd = ft_calloc(1, sizeof(t_format_cmd));
	size = exp_size(&list, &node);
	cmd->cmd_name = (t_token *)(node->data);
	cmd->infile = store_infile(&list, size, node);
	cmd->outfile = store_outfile(&list, size, node);
	cmd->option = store_option(&list, size, node);
	cmd->argument = store_argument(&list, size, node);
	return (cmd);
}


