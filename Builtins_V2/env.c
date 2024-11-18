/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:06:14 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/18 18:31:16 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int mini_env(char ** envp)
{
    int i;
    size_t w_bytes;
    i = -1;
    while(envp[++i]) 
    {
        w_bytes = write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
        if (w_bytes != ft_strlen(envp[i]))
            return (125);
        w_bytes = write(STDOUT_FILENO, "\n", 1);
        if (w_bytes != 1)
            return (125);
    }
    return (0);
}
