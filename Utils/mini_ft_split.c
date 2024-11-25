/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:41:18 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 17:57:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

static void	mini_free_split(char **split, char *s_trimmed, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(split[i]);
		i++;
	}
	free(s_trimmed);
	free(split);
}

static char	*mini_count_split(t_heap * heap, const char *s, char c, size_t *sub_str_count)
{
	char	set[2];
	char	*s_trimmed;
	size_t	i;

	i = 0;
	*sub_str_count = 1;
	set[0] = c;
	set[1] = '\0';
	s_trimmed = mini_ft_strtrim(heap,s, set);
	if (!s_trimmed)
		return (NULL);
	if (*s_trimmed == 0)
		(*sub_str_count)--;
	while (s_trimmed[i])
	{
		if (s_trimmed[i] == c && s_trimmed[i + 1] != c)
			(*sub_str_count)++;
		i++;
	}
	return (s_trimmed);
}

static char	**mini_make_split(t_heap * heap,char **split, char *s_trimmed, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (s_trimmed[i])
	{
		start = i;
		while (s_trimmed[i] != c && s_trimmed[i])
			i++;
		split[j] = mini_ft_substr(heap,s_trimmed, start, i -start);
		if (!split[j])
		{
			mini_free_split(split, s_trimmed, j + 1);
			return (NULL);
		}
		j++;
		while (s_trimmed[i] == c && c != '\0')
			i++;
	}
	split[j] = NULL;
	return (split);
}

char	**mini_ft_split(t_heap * heap,char const *s, char c)
{
	size_t	sub_str_count;
	char	**split;
	char	*s_trimmed;

	s_trimmed = mini_count_split(heap,s, c, &sub_str_count);
	// split = malloc(sizeof(char *) * (sub_str_count + 1));
	split = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*split) * (sub_str_count + 1));
	if (!split)
	{
		free(s_trimmed);
		return (NULL);
	}
	return (mini_make_split(heap,split, s_trimmed, c));
}
