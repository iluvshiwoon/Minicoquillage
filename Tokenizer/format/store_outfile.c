#include "format.h"

static int	count_outfile(t_double_link_list **list_o, int size, t_double_link_node *node)
{
	int					i;
	t_double_link_list	*list;
	// t_double_link_node	*node;

	list = *list_o;
	// node = list->first_node;
	i = 0;
	while (size--)
	{
		if (((t_token *)node->data)->value[0] == '>')
		{
			i++;
		}
		node = node->next;
	}
	return (i);
}


t_token **store_outfile(t_double_link_list **list, int size, t_double_link_node *node)
{
	t_token				**store;
	// t_double_link_node	*node;
	int					count;
	int					i;

	// node = (*list)->first_node;
	i = 0;
	count = count_outfile(list, size, node);
	store = (t_token **)malloc((1 + count) * sizeof(t_token*));
	while (node && size--)
	{
		if (node && ((t_token *)node->data)->type == REDIRECTION)
		{
			if (((t_token *)node->data)->value[0] == '>')
			{
				node = node->next;
				*store = (t_token *)node->data;
				store++;
				i++;
			}
		}
		node = node->next;
	}
	*store = NULL;
	return (store - i);
}

