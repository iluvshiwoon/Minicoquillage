/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:14:29 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 15:15:20 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	build_type(char **type)
{
	type[COMMAND] = "COMMAND";
	type[ARG] = "ARGUMENT";
	type[PIPE] = "PIPE";
	type[REDIRECTION] = "REDIRECTION";
	type[HERE_DOC] = "HERE DOC";
	type[OPTION] = "OPTION";
	type[AND] = "AND";
	type[OR] = "OR";
	type[OPEN_PARENTHESIS] = "OPEN PARENTHESIS";
	type[CLOSE_PARENTHESIS] = "CLOSE PARENTHESIS";
	type[CMD_SEP] = "COMMAND SEPARATOR";
	type[R_FILE] = "FILE";
}

void	print_list(t_double_link_list *tokens_lists)
{
	size_t				i;
	t_double_link_node	*node;
	t_token				*token;
	char				*type[12];

	build_type(type);
	i = 0;
	node = tokens_lists->first_node;
	printf("\n\033[47;30m TOKENS \033[0m\n");
	while (node)
	{
		token = node->data;
		printf("    \033[1;4;31mType\033[24m:\033[0m \033[41m%s\033[0m\n",
			type[token->type]);
		printf("        \033[1;4;32mValue\033[24m:\033[0m %s$\n", token->value);
		node = node->next;
	}
}

void	print_csv(t_double_link_list *tokens_lists)
{
	size_t				i;
	t_double_link_node	*node;
	t_token				*token;
	char				*type[12];

	build_type(type);
	i = 0;
	node = tokens_lists->first_node;
	while (node)
	{
		token = node->data;
		printf("%s: %s / ", type[token->type], token->value);
		node = node->next;
	}
}
