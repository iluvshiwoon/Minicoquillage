#include "format.h"

static int	count_argument(t_double_link_list **list_o, int size, t_double_link_node *node)
{
	int					i;
	// t_double_link_node	*node;
	t_double_link_list	*list;

	list = *list_o;
	// node = list->first_node;
	i = 0;
	while (size--)
	{
		if (((t_token *)node->data)->type == ARG)
		{
			i++;
		}
		node = node->next;
	}
	return (i);
}


t_token **store_argument(t_double_link_list **list, int size, t_double_link_node *node)
{
	t_token				**store;
	// t_double_link_node	*node;
	int					count;
	int					i;

	// node = (*list)->first_node;
	i = 0;
	count = count_argument(list, size, node);
	store = (t_token **)malloc((1 + count) * sizeof(t_token*));
	while (node && size--)
	{
		if (node && ((t_token *)node->data)->type == ARG)
		{
				*store = (t_token *)node->data;
				store++;
				i++;
		}
		node = node->next;
	}
	*store = NULL;
	return (store - i);
}
