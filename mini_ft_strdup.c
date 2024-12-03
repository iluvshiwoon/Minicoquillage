/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:47:55 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*mini_ft_strdup(t_mini *mini, const char *s)
{
	char			*s_dupe;
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	s_dupe = wrap_malloc(mini, (i + 1) * sizeof(char));
	if (!s_dupe)
		return (0);
	i = 0;
	while (s[i])
	{
		s_dupe[i] = s[i];
		i++;
	}
	s_dupe[i] = s[i];
	return (s_dupe);
}
