/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:57:06 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 15:24:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

void	init_expand(t_open_quote *open, t_control_dll *control, size_t *j,
		t_double_link_node *node)
{
	open->double_quote = 0;
	open->single_quote = 0;
	control->token = node->data;
	control->token->quote = NONE;
	*j = 0;
}

int	handle_quote(t_control_dll *control, t_open_quote *open, size_t j)
{
	if (control->token->value[j] == '"' && !open->single_quote
		&& !open->double_quote)
	{
		open->double_quote = 1;
		return (EXIT_SUCCESS);
	}
	else if (control->token->value[j] == '\'' && !open->single_quote
		&& !open->double_quote)
	{
		open->single_quote = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
