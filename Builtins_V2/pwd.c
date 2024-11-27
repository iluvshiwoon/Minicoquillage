/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:38:45 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 18:38:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	mini_pwd(void)
{
	char	*cwd;
	size_t	w_bytes;
	int		r_value;

	cwd = getcwd(NULL, 0);
	w_bytes = 0;
	r_value = 0;
	if (cwd)
	{
		w_bytes = write(1, cwd, ft_strlen(cwd));
		w_bytes += write(1, "\n", 1);
		if (w_bytes != ft_strlen(cwd) + 1)
			r_value = 1;
		free(cwd);
	}
	return (r_value);
}
