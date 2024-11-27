/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:17:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 11:18:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	here_assign(char *to_expand, char *expanded)
{
	int				j;
	int				l;
	t_open_quote	open;

	open.double_quote = 0;
	open.single_quote = 0;
	j = -1;
	l = -1;
	while (to_expand[++j])
	{
		if (_handle_quote(to_expand[j], &open) == EXIT_SUCCESS)
			;
		else if (to_expand[j] == '"' && open.double_quote)
			open.double_quote = 0;
		else if (to_expand[j] == '\'' && open.single_quote)
			open.single_quote = 0;
		else
			expanded[++l] = to_expand[j];
		if (!to_expand[j])
			break ;
	}
}

int	here_count(char *str)
{
	int				i;
	int				count;
	t_open_quote	open;

	i = -1;
	count = 0;
	open.double_quote = 0;
	open.single_quote = 0;
	while (str[++i])
	{
		if (_handle_quote(str[i], &open) == EXIT_SUCCESS)
			;
		else if (str[i] == '"' && open.double_quote)
			open.double_quote = 0;
		else if (str[i] == '\'' && open.single_quote)
			open.single_quote = 0;
		else
			++count;
		if (!str[i])
			break ;
	}
	return (count);
}

bool	here_is_empty_quote(char *to_expand)
{
	if (to_expand[0] == '\'' || to_expand[0] == '"')
	{
		if (to_expand[1] == to_expand[0])
			return (true);
	}
	return (false);
}

char	*_quote(t_heap *heap, char *to_expand)
{
	char	*expanded;
	int		i;
	int		count;

	i = -1;
	expanded = NULL;
	while (to_expand[++i])
	{
		count = here_count(to_expand);
		if (!count && here_is_empty_quote(to_expand))
		{
			expanded = wrap_malloc(heap->heap_allocated, heap->list,
					sizeof(char));
			expanded[0] = '\0';
		}
		else if (count)
		{
			expanded = wrap_malloc(heap->heap_allocated, heap->list,
					sizeof(char) * (count + 1));
			expanded[count] = '\0';
			here_assign(to_expand, expanded);
		}
	}
	return (expanded);
}
