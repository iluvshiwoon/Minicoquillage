/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:59:59 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 19:01:44 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

void	sigint_handler(int sig)
{
	printf("\n");
	if (g_signal == 999)
		return ;
	g_signal = sig;
	close(STDIN_FILENO);
}

void	sigquit_handler(int sig)
{
	g_signal = sig;
}

void    handle_sig(void)
{
	struct sigaction	sa;
    struct sigaction    sb;

	sa.sa_handler = sigint_handler;
	sb.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sb.sa_mask);
	sa.sa_flags = 0;
	sb.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}
