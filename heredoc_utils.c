/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:11 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:57:12 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

size_t	_max_len(size_t len1, size_t len2)
{
	if (len1 >= len2)
		return (len1);
	return (len2);
}

void	_write_listen(int fd, char *line)
{
	size_t	r_value;

	r_value = write(fd, line, ft_strlen(line));
	r_value += write(fd, "\n", 1);
	if (r_value != ft_strlen(line) + 1)
		ft_printf_fd(STDERR_FILENO, "minicoquillage: heredoc: %s\n",
			strerror(errno));
}
