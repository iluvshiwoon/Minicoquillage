/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:03:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/18 14:04:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../Minicoquillage.h"

void	assign_quote(t_double_link_node *node)
{
	t_control_dll	control;
	t_open_quote	open;
	char			*temp;
	size_t			j;

	init_expand(&open, &control, &j, node);
	while (control.token->value[j])
	{
        if (handle_quote(&control, &open, j) == EXIT_SUCCESS)
			j = j;
        else if (control.token->value[j] == '"' && open.double_quote)
		{
			open.double_quote = 0;
            control.token->quote = DOUBLE;
		}
        else if (control.token->value[j] == '\'' && open.single_quote)
		{
			open.single_quote = 0;
            control.token->quote = SINGLE;
		}
		++j;
	}
}
