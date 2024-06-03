#include "exec.h"
#include "../Tokenizer/Tokenizer.h"

int count_redirect(t_double_link_list *token_list)
{
	int					count;
	t_double_link_node	*node;
	t_token				*token;

	node = token_list->first_node;
	while (node)
	{
		if (token->type == AND || token->type == OR || token->type == PIPE)
		{
			node = node->next;
			count++;
		}
		node = node->next;
	}
	return (count);
}

t_double_link_node *ast(t_double_link_node *start, t_double_link_node *end)
{
	t_double_link_node *next = start->next;
	t_token *data_s = (t_token *)start;
	t_token *data_n = (t_token *)next;

}
