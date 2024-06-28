#include "../../Minicoquillage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// void	*my_realloc(void *ptr, size_t new_size)
// {
// 	if (new_size == 0)
// 	{
// 		free(ptr);
// 		return NULL;
// 	}
// 	if (!ptr)
// 		return malloc(new_size);
// 	void *new_ptr = malloc(new_size);
// 	if (!new_ptr)
// 		return NULL;
// 	ft_memcpy(new_ptr, ptr, new_size - 1);
// 	free(ptr);
// 	return new_ptr;
// }



t_double_link_list	**cmd_isolated(t_double_link_list **cpy_list, t_double_link_list **cmds)
{
	t_token				*tok;
	t_double_link_node	*end;
	t_double_link_node	*tmp;

	tmp = (*cpy_list)->first_node;
	tok = (t_token *)tmp->data;
	while (tmp && tok->type != OR && tok->type != AND && tok->type != CLOSE_PARENTHESIS)
	{
		if (tok->type == COMMAND)
		{
			end = malloc(sizeof(t_double_link_node));
			if (!end)
				return (NULL);
			end->data = (t_token *)tmp->data;
			(*cmds)->pf_insert_end(*cmds, end);
		}
		tmp = tmp->next;
		if (tmp)
			tok = (t_token *)tmp->data;
	}
	return (cmds);
}


void	my_cmds(t_double_link_list **list)
{
	t_double_link_list	*cmds;
	t_double_link_list	**cpy_list;
	t_double_link_node	*cmds_node;


	cpy_list = list;
	cmds = malloc (sizeof(*cmds));
	if (!cmds)
		return;
	init_list(cmds);
	cmds = *(cmd_isolated(cpy_list, &cmds));
	cmds_node = cmds->first_node;
	if (!cmds->first_node)
		printf("il y a rien");

}
