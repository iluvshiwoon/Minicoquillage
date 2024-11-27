/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:36:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	__print_cd(char **path, t_heap *heap, char **envp)
{
	(*path) = _getenv(heap, "OLDPWD", envp, 0);
	if (!(*path))
	{
		(*path) = NULL;
		printf("minicoquillage: cd: OLDPWD not set\n");
	}
	else
		printf("%s\n", (*path));
}
