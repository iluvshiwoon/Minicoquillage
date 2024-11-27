/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:08:14 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	populate_first_token1(t_control_dll *control, size_t len_token)
{
	if (!ft_strncmp(control->token->value, "<<", len_token))
		control->token->type = HERE_DOC;
	else if (!ft_strncmp(control->token->value, ";", len_token))
		control->token->type = CMD_SEP;
	else if (!ft_strncmp(control->token->value, "&&", len_token))
		control->token->type = AND;
	else if (!ft_strncmp(control->token->value, "||", len_token))
		control->token->type = OR;
	else if (!ft_strncmp(control->token->value, "&|", len_token))
		control->token->type = AND;
	else if (!ft_strncmp(control->token->value, "|&", len_token))
		control->token->type = AND;
}

int	is_option(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i >= 2 && str[i] == '-')
			return (EXIT_FAILURE);
		else if (!i && str[i] != '-')
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	add_type(t_control_dll *control, int type, int *cmd)
{
	control->token->type = type;
	*cmd = 0;
}
