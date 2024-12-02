/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:00:59 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*mini_ft_strjoin(t_mini *mini, char const *s1, char const *s2)
{
	size_t	l_s1;
	size_t	l_s2;
	char	*j_string;

	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	j_string = wrap_malloc(mini,  (l_s2 + l_s1) * sizeof(char)
			+ sizeof(char));
	ft_strlcpy(j_string, s1, l_s1 + 1);
	ft_strlcpy(j_string + l_s1, s2, l_s2 + 1);
	return (j_string);
}
