#include "format.h"


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


int exp_size(t_double_link_list **list)
{
	// t_double_link_list *list;
	t_double_link_node *node;
	int i;

	i = 0;
	// list = *list_o;
	node = (*list)->first_node;
	while (node != NULL && node->data != NULL && expression((t_token *)node->data) == 1)
	{
		node  = node->next;
		i++;
	}
	printf("%d\n", i);
	return (i);
}


t_format_cmd	*format_array(t_double_link_list **list_o)
{
	t_double_link_list *list;
	t_format_cmd	*cmd;
	int				size;

	list = *list_o;
	// cmd = tok_list;
	cmd = ft_calloc(1, sizeof(t_format_cmd));
	size = exp_size(&list);
	cmd->cmd_name = (t_token *)((list)->first_node)->data;
	cmd->infile = store_infile(&list, size);
	cmd->outfile = store_outfile(&list, size);
	cmd->option = store_option(&list, size);
	cmd->argument = store_argument(&list, size);
	return (cmd);
}
