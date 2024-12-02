/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:43:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:18:37 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	error_exit(char *msg, t_mini *mini)
{
	if (msg)
		ft_printf_fd(STDERR_FILENO,"%s", msg);
    close_fds(mini->fds);
	free_heap(mini, true);
	exit(EXIT_FAILURE);
}
