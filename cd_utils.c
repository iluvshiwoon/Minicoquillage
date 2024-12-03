/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:36:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 23:15:05 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__print_cd(t_mini *mini, char **path)
{
	size_t	w_bytes;

	(*path) = _getenv(mini, "OLDPWD");
	if (!(*path))
	{
		(*path) = NULL;
		ft_printf_fd(STDERR_FILENO, "minicoquillage: cd: OLDPWD not set\n");
	}
	else
	{
		w_bytes = write(STDOUT_FILENO, (*path), ft_strlen((*path)));
		if (w_bytes != ft_strlen((*path)))
		{
			ft_printf_fd(STDERR_FILENO,
				"minicoquillage: cd: write error: No space left on device\n");
			mini->status = 1;
		}
	}
}
