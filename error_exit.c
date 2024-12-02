/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:43:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 00:40:35 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	error_exit(char *msg, t_mini *mini)
{
	if (msg)
		printf("%s", msg);
	free_heap(mini, true);
	exit(EXIT_FAILURE);
}
