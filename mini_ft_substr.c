/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_substr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:13:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

static char	*create_sub(const char *s, char *sub, unsigned int start,
		size_t len)
{
	size_t	i;

	i = 0;
	while (s[start + i] && i != len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*mini_ft_substr(t_mini *mini, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	l_s;

	i = 0;
	l_s = ft_strlen(s);
	if (start > l_s)
	{
		sub = wrap_malloc(mini,  sizeof(*sub));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	while (s[start + i] && i != len)
		i++;
	sub = wrap_malloc(mini,  i * sizeof(*sub) + sizeof(*sub));
	if (!sub)
		return (NULL);
	else
	{
		sub = create_sub(s, sub, start, len);
		return (sub);
	}
}
