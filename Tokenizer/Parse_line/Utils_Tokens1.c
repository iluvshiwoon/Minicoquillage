/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:41:09 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/15 15:06:31 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../Minicoquillage.h"

void	add_token(size_t i, size_t j, char *line, t_control_dll *control)
{
	char	*temp;

	control->node = wrap_malloc(control->heap_allocated,control->heap_allocated->tokens,sizeof(*control->node));
    *control->node = (t_double_link_node){};
	control->token = wrap_malloc(control->heap_allocated,control->heap_allocated->tokens,sizeof(*control->token));
    *control->token = (t_token){};
	control->token->type = COMMAND;
	temp = wrap_malloc(control->heap_allocated,control->heap_allocated->tokens,sizeof(char) * (j - i + 1));
	ft_strlcpy(temp, line + i, j - i + 1);
	control->token->value = temp;
	control->node->data = control->token;
	control->list->pf_insert_end(control->list, control->node);
}

int	check_quote(char c, t_open_quote *open)
{
	if (c == '"' && !open->single_quote && !open->double_quote)
		open->double_quote = 1;
	else if (c == '\'' && !open->single_quote && !open->double_quote)
		open->single_quote = 1;
	else if (c == '"' && open->double_quote)
		open->double_quote = 0;
	else if (c == '\'' && open->single_quote)
		open->single_quote = 0;
	else
		return (0);
	return (1);
}

size_t	init_create_tokens(t_open_quote *open, t_control_dll *control,
		char *line, size_t *j)
{
	*j = 0;
	open->double_quote = 0;
	open->single_quote = 0;
	control->list = wrap_malloc(control->heap_allocated,control->heap_allocated->tokens,sizeof(*control->list));
    *control->list = (t_double_link_list){};
	*j = skip_space(line, *j);
	if (ft_isspace(line[*j]))
		*j += 1;
	init_list(control->list);
	return (*j);
}

t_double_link_list	*expand_nodes(size_t i, size_t j, t_control_dll *control,
		char *line)
{
	if (i != j && j <= ft_strlen(line))
		add_token(i, j, line, control);
	control->node = control->list->first_node;
	while (control->node)
	{
		// expand_tokens(control->node);
        assign_quote(control->node);
		control->node = control->node->next;
	}
    // control->token = malloc(sizeof(*(control->token)));
    // control->node = malloc(sizeof(*control->node));
    // *(control->token) = (t_token){};
    // control->token->type = EOE;
    // control->node->data = control->token;
    // control->list->pf_insert_end(control->list,control->node);
	return (control->list);
}
