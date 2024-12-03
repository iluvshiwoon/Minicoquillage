/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:50:52 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 02:39:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

typedef struct s_glob
{
	void			*file;
	struct s_glob	*next;
}					t_glob;

typedef struct s_match
{
	long long		gx;
	long long		sx;
	long long		lastgx;
	long long		nextsx;
}					t_match;

int					globbing(const char *str, const char *glob);
t_glob				*glob(t_mini *mini, const char *pattern, bool *litteral);
int					match(const char *str, const char *glob, bool *litteral);
int					max_file(void);
#endif
