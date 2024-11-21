/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:25:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/21 21:27:58 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int	_is_option(char *msg, int * j)
{
    int	i;
    bool option;

    i = 0;
    *j = 0;
    option = false;
    if (msg[i] == '-')
        i++;
    while (msg[i])
    {
        if (msg[i] == 'n')
            option = true;
        else if (!ft_isspace(msg[i]))
        {
            option = false;
            break;
        }
        if (i > 1 && ft_isspace(msg[i]))
        {
            i++;
            break;
        }
        i++;
    }
    if (option)
        *j = i;
    return (option);
}

int mini_echo(char **args)
{
	int	opt;
    long long r_value;
    int i;
    int j;
    bool first;

    i = 1;
    j = 0;
    opt = 0;
    r_value = 0;
    first = true;
    while (args[i])
    { 
        opt = _is_option(args[i],&j);
        if (!opt)
            break;
        else
            r_value = 1;
        if (args[i][j] == '\0')
            i++;
        else 
            break;
    }
    opt = r_value;
    while (args[i])
    {
        if (first)
            _is_option(args[i],&j);
        if (!first)
        {
            r_value = write(1, " ", 1);
            if (r_value != 1)
                return (1);
        }
        r_value = write(1, args[i]+j, ft_strlen(args[i])-j);
        if (r_value != (long long)ft_strlen(args[i])-j)
            return (1);
        i++;
        first = false;
    }
    if (!opt)
        r_value = write(1, "\n", 1);
    if (r_value != 1 && !opt)
        return (1);
    return (0);
}
