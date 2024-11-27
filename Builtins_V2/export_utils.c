/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:42:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 18:44:04 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	_var_name_cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] != '=' && s2[i] != '=')
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

int	_search_var(t_heap *heap, char *arg, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (_var_name_cmp(env[i], arg) == 0)
		{
			env[i] = mini_ft_strdup(heap->heap_allocated, heap->env, arg);
			return (0);
		}
	}
	return (1);
}
