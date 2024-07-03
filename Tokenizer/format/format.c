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
	t_double_link_node	*node;
	int					i;

	i = 0;
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
	cmd = ft_calloc(1, sizeof(t_format_cmd));
	size = exp_size(&list);
	cmd->cmd_name = (t_token *)((list)->first_node)->data;
	cmd->infile = store_infile(&list, size);
	cmd->outfile = store_outfile(&list, size);
	cmd->option = store_option(&list, size);
	cmd->argument = store_argument(&list, size);
	return (cmd);
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
	tab[i++] = cmd->cmd_name->value;
	while (cmd->option[j])
		tab[i++] = cmd->option[j++]->value;
	j = 0;
	while (cmd->argument[j])
		tab[i++] = cmd->argument[j++]->value;
	tab[i] = NULL;
	j = 0;
		printf("format.c - tab_cmd :\n");
	while (tab[j])
		printf("%s\n", tab[j++]);
	return (tab);
}

void	for_exec(t_pipex **exe, t_double_link_list **list_o)
{
	t_format_cmd	*format;
	char			**tab;

	format = format_array(list_o);
	tab = tab_cmd(format);
	(*exe)->cmds = &tab[0];
	(*exe)->path_cmd = tab;
}
