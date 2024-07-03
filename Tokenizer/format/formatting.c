#include "../../Minicoquillage.h"
#include "format.h"
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


// (f | o | p && k) && i j k
// cmd seul
// cmd entre parenthese
// cmd seul avec arg
// multiple cmd


 // condition qui fail (cmd) || cmd retourn 1 au lieu de 2
int	total_cmd2(t_double_link_list **list_o, t_double_link_node **first)
{
	t_double_link_node	*node;
	t_token				*tok;
	int					i;

	i = 0;
	if (!first)
		return (0);
	node = *first;
	if (!node || !(node->data))
		return (0);
	tok = (t_token *)node->data;
	if (node && tok->type == COMMAND)
		return  1 + total_cmd2(list_o, &node->next);
	else if (tok->type == OPEN_PARENTHESIS)
	{
		while (node && tok->type != CLOSE_PARENTHESIS)
			node = node->next;
		printf("%s\n", ((t_token *)node->next->data)->value);
		return 1 + total_cmd2(list_o, &node->next);
	}
	else if (node && node != (*list_o)->last_node)
		return  total_cmd2(list_o, &node->next);
	else
		return (0);
}


int	size_option(t_format_cmd *cmd)
{
	t_token	**options;
	int		i;

	i = 0;
	options = cmd->option;
	while(options[i])
		i++;
	return (i);
}

int	size_argument(t_format_cmd *cmd)
{
	t_token	**arguments;
	int		i;

	i = 0;
	arguments = cmd->argument;
	while(arguments[i])
		i++;
	return (i);
}

int	size_cmd(t_format_cmd *cmd)
{
	int	i;
	int	size_opt;
	int	size_arg;

	i = 1;
	size_opt = size_option(cmd);
	size_arg = size_argument(cmd);
	return (i + size_arg + size_opt);
}
