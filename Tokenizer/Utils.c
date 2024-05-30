/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/30 17:03:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int ft_sep(int c)
{
    return (c == '&' || c == '|' || c == '>' || c == '<');
}

void build_type(char ** type)
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
}

void	print_list(t_double_link_list *tokens_lists)
{
	size_t				i;
	t_double_link_node	*node;
    t_token * token;
    char *type[10];

    build_type(type);
	i = 0;
	node = tokens_lists->first_node;
    printf("\n\033[47;30m TOKENS \033[0m\n");
	while (node)
	{
        token = node->data;
        printf("    \033[1;4;31mType\033[24m:\033[0m \033[41m%s\033[0m\n", type[token->type]);
		printf("        \033[1;4;32mValue\033[24m:\033[0m %s$\n", token->value);
		node = node->next;
	}
}

size_t	count_node(t_double_link_list *list)
{
	t_double_link_node	*node;
	size_t				i;

	node = list->first_node;
	i = 0;
	while (node)
	{
		node = node->next;
		++i;
	}
	if (!i)
		return (dl_free_list(list), exit(EXIT_FAILURE), i);
	return (i);
}
