/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:36:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:18:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__print_cd(t_mini * mini, char **path)
{
	(*path) = _getenv(mini, "OLDPWD");
	if (!(*path))
	{
		(*path) = NULL;
		ft_printf_fd(STDERR_FILENO,"minicoquillage: cd: OLDPWD not set\n");
	}
	else
		ft_printf_fd(STDOUT_FILENO,"%s\n", (*path));
}
