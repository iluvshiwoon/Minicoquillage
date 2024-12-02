/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:42:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:33:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int	_var_name_cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] != '=' && s2[i] != '=')
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

int	_search_var(t_mini *mini, char *arg)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
	{
		if (_var_name_cmp(mini->envp[i], arg) == 0)
		{
			mini->envp[i] = mini_ft_strdup(mini, arg);
			return (0);
		}
	}
	return (1);
}
