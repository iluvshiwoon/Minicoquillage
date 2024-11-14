/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:25:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/14 16:54:14 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	_is_option(char *msg)
{
    int	i;

    i = 0;
    if (msg[i] == '-')
        i++;
    while (msg[i])
    {
        if (msg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int mini_echo(char **args)
{
	int	opt;
    long long r_value;
    int i;
    bool first;

    i = 1;
    opt = 0;
    r_value = 0;
    first = true;
    while (_is_option(args[i]))
    {
        opt = 1;
        i++;
    }
    while (args[i])
    {
        if (!first)
        {
            r_value = write(1, " ", 1);
            if (r_value != 1)
                return 55;
        }
        r_value = write(1, args[i], ft_strlen(args[i]));
        if (r_value != (long long)ft_strlen(args[i]))
            return (55); // change error 
        i++;
        first = false;
    }
    if (!opt)
        r_value = write(1, "\n", 1);
    if (r_value != 1)
        return (55);
    return (0);
}
