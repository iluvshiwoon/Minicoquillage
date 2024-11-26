/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:25:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 00:40:52 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void __is(char * msg, int * i, int * j, bool * option)
{
    *i = 0;
    *j = 0;
    *option = false;
    if (msg[*i] == '-')
        (*i)++;
}

int	_is_option(char *msg, int * j)
{
    int	i;
    bool option;

    __is(msg,&i,j,&option);
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

void __echo(char ** args, t_index * index, int * opt, long long * r_value)
{
    index->i = 1;
    index->j = 0;
    *opt = 0;
    *r_value = 0;

    while (args[index->i])
    { 
        *opt = _is_option(args[index->i],&index->j);
        if (!(*opt))
            break;
        else
            (*r_value) = 1;
        if (args[index->i][index->j] == '\0')
            index->i++;
        else 
            break;
    }
    *opt = (*r_value);
}

int r_echo(int opt)
{
    long long r_value;

    r_value = 0;
    if (!opt)
        r_value = write(1, "\n", 1);
    if (r_value != 1 && !opt)
        return (1);
    return (0);
}

int mini_echo(char **args)
{
    t_index index;
	int	opt;
    long long r_value;
    bool first;

    first = true;
    __echo(args,&index,&opt,&r_value);
    while (args[index.i])
    {
        if (first)
            _is_option(args[index.i],&index.j);
        if (!first)
        {
            r_value = write(1, " ", 1);
            if (r_value != 1)
                return (1);
        }
        r_value = write(1, args[index.i]+index.j, ft_strlen(args[index.i])-index.j);
        if (r_value != (long long)ft_strlen(args[index.i])-index.j)
            return (1);
        index.i++;
        first = false;
    }
    return (r_echo(opt));
}
