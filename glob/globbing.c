/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:50:46 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 15:50:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_init_match(t_match *match)
{
	match->gx = 0;
	match->sx = 0;
	match->lastgx = -1;
	match->nextsx = 0;
}

bool	_change_last(const char *str, const char *glob, bool *litteral,
		t_match *m)
{
	char	c;
	bool	lit;

	c = glob[m->gx];
	lit = litteral[m->gx];
	if (c == '*' && lit == false)
	{
		m->lastgx = m->gx;
		m->nextsx = m->sx + 1;
		m->gx++;
		return (true);
	}
	else
	{
		if (m->sx < (long long)ft_strlen(str) && str[m->sx] == c)
		{
			m->gx++;
			m->sx++;
			return (true);
		}
	}
	return (false);
}

int	_match(const char *str, const char *glob, bool *litteral, t_match *m)
{
	while (m->gx < (long long)ft_strlen(glob)
		|| m->sx < (long long)ft_strlen(str))
	{
		if (m->gx < (long long)ft_strlen(glob))
		{
			if (_change_last(str, glob, litteral, m) == true)
				continue ;
		}
		if (m->nextsx > 0 && m->nextsx <= (long long)ft_strlen(str))
		{
			m->gx = m->lastgx;
			m->sx = m->nextsx;
			continue ;
		}
		return (0);
	}
	return (1);
}

int	match(const char *str, const char *glob, bool *litteral)
{
	t_match	m;

	_init_match(&m);
	return (_match(str, glob, litteral, &m));
}
