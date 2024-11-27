/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:49:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 15:49:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	max_file(void)
{
	const char		*path;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	path = ".";
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		i++;
	}
	closedir(dir);
	return (i);
}
