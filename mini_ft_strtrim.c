/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

static int	mini_ft_isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	mini_find_l_trimmed(char const *s1, char const *set,
		size_t *l_trim_beg)
{
	size_t	l_s1;
	size_t	l_trim_end;
	size_t	l_trimmed;
	size_t	i;

	i = 0;
	l_trimmed = 0;
	*l_trim_beg = 0;
	l_trim_end = 0;
	l_s1 = ft_strlen(s1);
	while (s1[i] && mini_ft_isinset(s1[i], set))
		i++;
	*l_trim_beg = i;
	if (i != l_s1)
	{
		i = l_s1 - 1;
		while (s1[i] && mini_ft_isinset(s1[i], set))
			i--;
		l_trim_end = l_s1 - 1 - i;
	}
	l_trimmed = l_s1 - *l_trim_beg - l_trim_end;
	return (l_trimmed);
}

char	*mini_ft_strtrim(t_mini *mini, char const *s1, char const *set)
{
	char	*trimmed;
	size_t	l_trimmed;
	size_t	l_trim_beg;

	l_trimmed = mini_find_l_trimmed(s1, set, &l_trim_beg);
	trimmed = wrap_malloc(mini,  sizeof(*trimmed)
			* l_trimmed + sizeof(*trimmed));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + l_trim_beg, l_trimmed + 1);
	return (trimmed);
}
