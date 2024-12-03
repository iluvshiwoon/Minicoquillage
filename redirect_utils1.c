/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:05 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:38:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	_error(char *error, int *skip, int *status, char *filename)
{
	*skip = 1;
	*status = 1;
	ft_printf_fd(STDERR_FILENO, error, filename);
}

void	__red(t_mini *mini, char *globbed, t_atom *atom, t_exec *exec)
{
	if (atom->append[exec->i])
		atom->out_fd = m_open(mini, globbed, O_WRONLY | O_APPEND, 0);
	else
		atom->out_fd = m_open(mini, globbed, O_WRONLY, 0);
}
