/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/21 12:23:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	ft_sep(int c)
{
	return (c == '&' || c == '|' || c == '>' || c == '<' || c == ';' || c == '('
		|| c == ')');
}
