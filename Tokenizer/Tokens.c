/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:29:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/29 17:43:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Minicoquillage.h"

void	expand_tokens(t_double_link_node *node)
{
	int		double_quote_open;
	char	*token;
	char	*temp;
	int		single_quote_open;
	size_t	j;

	double_quote_open = 0;
	single_quote_open = 0;
	token = node->data;
	j = 0;
	while (token[j])
	{
		if (token[j] == '"' && !single_quote_open && !double_quote_open)
			double_quote_open = 1;
		else if (token[j] == '\'' && !single_quote_open && !double_quote_open)
			single_quote_open = 1;
		else if (token[j] == '"' && double_quote_open)
			double_quote_open = expand_double_quote(&j, &token, &temp, &node);
		else if (token[j] == '\'' && single_quote_open)
			single_quote_open = expand_single_quote(&j, &token, &temp, &node);
		++j;
	}
}

t_double_link_list	*create_tokens(char *line)
{
	t_control_dll	control;
	t_open_quote	open;
	size_t			i;
	size_t			j;

	i = init_create_tokens(&open, &control, line, &j);
	while (line[j])
	{
		if (!check_quote(line[j], &open) && (ft_isspace(line[j])
				&& !open.single_quote && !open.double_quote))
		{
			add_token(i, j, line, control.list);
			j = skip_space(line, j);
			i = j + 1;
		}
		++j;
	}
	return (expand_nodes(i, j, &control, line));
}
