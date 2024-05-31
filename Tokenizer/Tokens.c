/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:29:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/31 16:44:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Minicoquillage.h"

void	expand_tokens(t_double_link_node *node)
{
	int		double_quote_open;
	char	*value;
	char	*temp;
	int		single_quote_open;
    t_token * token;
	size_t	j;

	double_quote_open = 0;
	single_quote_open = 0;
    token = node->data;
	value = token->value;
	j = 0;
	while (value[j])
	{
		if (value[j] == '"' && !single_quote_open && !double_quote_open)
			double_quote_open = 1;
		else if (value[j] == '\'' && !single_quote_open && !double_quote_open)
			single_quote_open = 1;
		else if (value[j] == '"' && double_quote_open)
			double_quote_open = expand_double_quote(&j, &value, &temp, &node);
		else if (value[j] == '\'' && single_quote_open)
			single_quote_open = expand_single_quote(&j, &value, &temp, &node);
		++j;
	}
}

int is_sep(char * line, size_t * i, size_t * j, t_control_dll * control)
{
    if (ft_sep(line[*j]))
    {
        if (*j && !ft_isspace(line[*j - 1]))
        {
            add_token(*i, *j, line, control);
            *i = *j;
        }
        while (ft_sep(line[*j]))
            (*j)++;
        return (1);
    }
    return (0);
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
		if (!check_quote(line[j], &open) && ((ft_isspace(line[j]) || is_sep(line, &i, &j, &control))
				&& !open.single_quote && !open.double_quote))
		{
			add_token(i, j, line, &control);
			j = skip_space(line, j);
            if (ft_isspace(line[j]))
			    i = j + 1;
            else 
                i = j;
		}
		++j;
	}
	return (expand_nodes(i, j, &control, line));
}
