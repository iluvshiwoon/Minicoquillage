/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:25:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/14 02:32:43 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	_is_option(char *msg)
{
	int	i;

	i = 0;
	if (msg[i] == '-')
		i++;
	else
		return (0);
	while (msg[i] == 'n')
		i++;
	if (msg[i] == ' ' && i >= 2)
		return (1);
	return (0);
}

int mini_echo(char **args)
{
	int	opt;
    int r_value;

	++args;
	opt = _is_option(*args);
	if (opt)
		++args;
	while (args)
	{
		ft_putstr_fd(*args, 1); // write fail ?
		if (args[1])
			r_value = write(1, " ", 1); // write fail?
	}
	if (!opt)
		r_value = write(1, "\n", 1);
    r_value++; // silence compiler
    return (0);
}
