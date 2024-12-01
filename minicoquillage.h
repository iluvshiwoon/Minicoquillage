/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicoquillage.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:37:42 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/01 17:11:12 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINICOQUILLAGE_H
# define MINICOQUILLAGE_H
# include <stdio.h>
# include <termios.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "42_MyLibC/mylibc.h"
# include "Utils.h"
# include "Tokenizer.h"
# include "Parser.h"
# include "expand.h"
# include "exec.h"
# include "glob.h"
# include "builtin.h"

void		_close(int fd);
void		handle_sig(void);

extern int	g_signal;
enum		e_mode
{
	INTERACTIVE,
	TEST
};

# ifndef MODE
#  define MODE INTERACTIVE
# endif
#endif
