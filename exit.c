/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:56:10 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 23:15:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"
#include <stdint.h>

static void	init_atoi(size_t *i, u_int64_t *value, int *l_digit, int *sign)
{
	*i = 0;
	*value = 0;
	*l_digit = 7;
	*sign = 1;
	return ;
}

int64_t	atoi64_safe(char *string, int *status)
{
	size_t		i;
	u_int64_t	value;
	int			l_digit;
	int			sign;

	if (init_atoi(&i, &value, &l_digit, &sign), string[0] == '-')
	{
		++i;
		l_digit = 8;
		sign = -1;
	}
	else if (string[0] == '+')
		++i;
	while (string[i])
	{
		if (ft_isdigit(string[i]) && ((value == INT64_MAX / 10 && string[i]
					- '0' > l_digit) || (value > INT64_MAX / 10)))
			return (*status = ERROR, 0);
		else if (ft_isdigit(string[i]))
			value = value * 10 + string[i] - '0';
		else
			return (*status = ERROR, 0);
		++i;
	}
	return (*status = SUCCESS, (int)value * sign);
}

void p_exit(t_mini * mini)
{
    if (!mini->pipe)
	    ft_printf_fd(STDERR_FILENO,"exit\n");
}

int	mini_exit(t_mini *mini, char **args)
{
	int		error;
	uint8_t	code;

	code = 0;
	if (args[1] == NULL)
	{
        close_fds(mini->fds);
		free_heap(mini, true);
        p_exit(mini);
		exit((mini->status + 256) % 256);
	}
	code = atoi64_safe(args[1], &error);
	if (error == ERROR)
		return (p_exit(mini),ft_printf_fd(STDERR_FILENO,"minicoquillage: exit: %s: numeric argument re\
quired\n", args[1]), close_fds(mini->fds), free_heap(mini, true), exit(2), 2);
	if (args[2])
		return (p_exit(mini),ft_printf_fd(STDERR_FILENO,"minicoquillage: exit: too many arguments"), 1);
    close_fds(mini->fds);
	free_heap(mini, true);
    p_exit(mini);
	exit((code + 256) % 256);
}
