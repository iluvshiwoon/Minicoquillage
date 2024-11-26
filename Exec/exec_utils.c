/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:40:29 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 15:53:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void _reset_fd(t_exec exec)
{
    dup2(exec.og_stdin, STDIN_FILENO);
    dup2(exec.og_stdout, STDOUT_FILENO);
}
