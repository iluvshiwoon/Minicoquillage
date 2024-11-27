/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 20:23:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
	char	*buffer;
	char	*prompt;
	char	*temp;
	t_heap	heap;

	heap.heap_allocated = heap_allocated;
	heap.list = heap_allocated->tokens;
	buffer = getcwd(NULL, 0);
	temp = buffer;
	if (!buffer)
		buffer = mini_ft_strdup(heap_allocated, heap.list, "FIXME");
	buffer = mini_ft_strdup(heap_allocated, heap.list, buffer);
	free(temp);
	prompt = last_ocur(buffer, '/');
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
