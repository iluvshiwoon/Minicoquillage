/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:29:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/18 15:44:37 by kgriset          ###   ########.fr       */
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
    token->quote = NONE;
	j = 0;
	while (value[j])
	{
		if (value[j] == '"' && !single_quote_open && !double_quote_open)
			double_quote_open = 1;
		else if (value[j] == '\'' && !single_quote_open && !double_quote_open)
			single_quote_open = 1;
		else if (value[j] == '"' && double_quote_open)
        {
			double_quote_open = expand_double_quote(&j, &value, &temp, &node);
            token->quote = DOUBLE;
        }
		else if (value[j] == '\'' && single_quote_open)
        {
			single_quote_open = expand_single_quote(&j, &value, &temp, &node);
            token->quote = SINGLE;
        }
		++j;
	}
}

int is_sep(char * line, size_t * i, size_t * j, t_control_dll * control)
{
    size_t k;
    size_t l;

    if (ft_sep(line[*i]) && !ft_sep(line[*j]))
        return (1);
    if (ft_sep(line[*j]))
    {
        if (*j && !ft_isspace(line[*j - 1]) && !ft_sep(line[*j - 1]))
        {
            add_token(*i, *j, line, control);
            *i = *j;
        }
        k = 2 + (*j == *i);
        while (ft_sep(line[*j]))
        {
            l = (*j == *i);
            --k;
            if ((line[*i] == '(' || line[*i] == ')' || line[*i] == ';' ) || (line[*i] != line[*j+l] && ft_sep(line[*j+l])) || !k)
            {
                if (*j==*i)
                    (*j)++;
                break;
            }
            (*j)++;
        }
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
        if (!check_quote(line[j], &open) && (
				 !open.single_quote && !open.double_quote) && (ft_isspace(line[j]) || is_sep(line, &i, &j, &control)))
		{
			add_token(i, j, line, &control);
			j = skip_space(line, j);
            if (ft_isspace(line[j]))
			    i = j + 1;
            else 
            {
                i = j;
                check_quote(line[i], &open);
            }
		}
        if (line[j])
		    ++j;
	}
	return (expand_nodes(i, j, &control, line));
}
