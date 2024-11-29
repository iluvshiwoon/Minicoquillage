/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/29 00:09:26 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*get_prompt(t_mini *mini, t_heap_allocated *heap_allocated)
{
	char	*prompt;

	prompt = build_prompt(mini, heap_allocated);
	return (prompt);
}

char	*r_prompt(t_mini *mini, char *temp)
{
	char				*r_value;
	t_heap_allocated	*heap_allocated;

	heap_allocated = &mini->heap_allocated;
	if (mini->status)
	{
		r_value = mini_ft_strjoin(heap_allocated, heap_allocated->input, temp,
				mini_ft_strjoin(heap_allocated, heap_allocated->input,
					mini_ft_strjoin(heap_allocated, heap_allocated->input,
						" via \1\033[1;34m\2", last_ocur(_getenv(&mini->heap,
								"SHELL", mini->envp, 0), '/') + 1),
					"\1\n🦪\2 \1\033[31m→\2 \1\033[0m\2"));
	}
	else
	{
		r_value = mini_ft_strjoin(heap_allocated, heap_allocated->input, temp,
				mini_ft_strjoin(heap_allocated, heap_allocated->input,
					mini_ft_strjoin(heap_allocated, heap_allocated->input,
						" via \1\033[1;34m\2", last_ocur(_getenv(&mini->heap,
								"SHELL", mini->envp, 0), '/') + 1),
					"\1\n🦪\2 \1\033[32m→\2 \1\033[0m\2"));
	}
	return (r_value);
}

char	*build_prompt(t_mini *mini, t_heap_allocated *heap_allocated)
{
	char	*buf;
	char	*prompt;
	char	*temp;
	bool	to_free;

	to_free = false;
	buf = _getenv(&mini->heap, "PWD", mini->envp, 0);
	if (!buf)
	{
		buf = getcwd(NULL, 0);
		to_free = true;
	}
	temp = buf;
	if (!buf)
		buf = mini_ft_strdup(heap_allocated, heap_allocated->tokens, ".");
	buf = mini_ft_strdup(heap_allocated, heap_allocated->tokens, buf);
	if (to_free == true)
		free(temp);
	prompt = last_ocur(buf, '/');
	prompt = mini_ft_strjoin(heap_allocated, heap_allocated->input,
			"\1\033[1;34m\2", prompt + 1);
	temp = mini_ft_strjoin(heap_allocated, heap_allocated->input, prompt,
			"\1\033[0m\2");
	prompt = r_prompt(mini, temp);
	return (prompt);
}

char	*last_ocur(char *string, char c)
{
	size_t	i;
	size_t	last;

	i = 0;
	last = 0;
	while (string[i])
	{
		if (string[i] == c)
			last = i;
		i++;
	}
	if (!last)
		return (string - 1);
	return (string + last);
}
