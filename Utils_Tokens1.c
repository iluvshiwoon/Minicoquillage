/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:41:09 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minicoquillage.h"

size_t	skip_space(char *line, size_t index)
{
	if (!line[index])
		return (index);
	while (ft_isspace(line[index]) && ft_isspace(line[index + 1]))
		++index;
	return (index);
}

void	add_token(size_t i, size_t j, char *line, t_mini *mini)
{
	char	*temp;

	mini->control.node = wrap_malloc(mini,
			 sizeof(*mini->control.node));
	*mini->control.node = (t_double_link_node){};
	mini->control.token = wrap_malloc(mini,
			 sizeof(*mini->control.token));
	*mini->control.token = (t_token){};
	mini->control.token->type = COMMAND;
	temp = wrap_malloc(mini, 
			sizeof(char) * (j - i + 1));
	ft_strlcpy(temp, line + i, j - i + 1);
	mini->control.token->value = temp;
	mini->control.node->data = mini->control.token;
	mini->control.list->pf_insert_end(mini->control.list, mini->control.node);
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

size_t	init_create_tokens(t_open_quote *open, t_mini *mini, char *line,
		size_t *j)
{
	*j = 0;
	open->double_quote = 0;
	open->single_quote = 0;
	mini->control.list = wrap_malloc(mini,
			 sizeof(*mini->control.list));
	*mini->control.list = (t_double_link_list){};
	*j = skip_space(line, *j);
	if (ft_isspace(line[*j]))
		*j += 1;
	init_list(mini->control.list);
	return (*j);
}

t_double_link_list	*expand_nodes(size_t i, size_t j, t_mini *mini, char *line)
{
	if (i != j && j <= ft_strlen(line))
		add_token(i, j, line, mini);
	mini->control.node = mini->control.list->first_node;
	while (mini->control.node)
	{
		mini->control.node = mini->control.node->next;
	}
	return (mini->control.list);
}
