/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ft_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:04:00 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minicoquillage.h"

static unsigned int	c_size(int n, unsigned int *p_n, int *sign)
{
	unsigned int	size;

	size = 1;
	*sign = 1;
	if (n < 0 && size++)
		*sign = -1;
	*p_n = *sign * n;
	while (*p_n / 10)
	{
		size++;
		*p_n /= 10;
	}
	return (size);
}

char	*mini_ft_itoa(t_heap *heap, int n)
{
	unsigned int	p_n;
	int				sign;
	unsigned int	size;
	char			*a;

	size = c_size(n, &p_n, &sign);
	a = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * (size
				+ 1));
	if (!a)
		return (NULL);
	a[size] = '\0';
	p_n = sign * n;
	while (p_n / 10)
	{
		a[--size] = '0' + p_n % 10;
		p_n /= 10;
	}
	a[--size] = '0' + p_n % 10;
	if (sign == -1)
		a[--size] = '-';
	return (a);
}
