#include "format.h"

static int	count_option(t_double_link_list **list_o, int size, t_double_link_node *node)
{
	int					i;
	// t_double_link_node	*node;
	t_double_link_list	*list;

	list = *list_o;
	// node = list->first_node;
	i = 0;
	while (size--)
	{
		if (((t_token *)node->data)->type == OPTION)
		{
			i++;
		}
		node = node->next;
	}
	return (i);
}


t_token **store_option(t_double_link_list **list, int size, t_double_link_node *node)
{
	t_token				**store;
	t_token				**end;
	// t_double_link_node	*node;
	int					count;

	// node = (*list)->first_node;
	count = count_option(list, size, node);
	store = (t_token **)malloc((1 + count) * sizeof(t_token*));
	end = store;
	while (node && size--)
	{
		if (node && ((t_token *)node->data)->type == OPTION)
		{
				*store = (t_token *)node->data;
				store++;
		}
		node = node->next;
	}
	*store = NULL;
	return (end);
}

