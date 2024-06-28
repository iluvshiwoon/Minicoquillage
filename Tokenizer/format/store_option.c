#include "format.h"

static int	count_option(t_double_link_list *list, int size)
{
	int					i;
	t_double_link_node	*node;

	node = list->first_node;
	i = 0;
	while (size--)
		if (((t_token *)node->data)->type == OPTION)
			i++;
	return (i);
}


t_token **store_option(t_double_link_list *list, int size)
{
	t_token				**store;
	t_double_link_node	*node;
	int					count;
	int					i;

	node = list->first_node;
	i = 0;
	count = count_option(list, size);
	store = (t_token **)malloc((1 + count) * sizeof(t_token));
	while (node && size--)
	{
		if (node && ((t_token *)node->data)->type == OPTION)
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

