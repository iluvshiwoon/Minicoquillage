/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/17 22:11:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

char	*get_prompt(t_heap_allocated *heap_allocated)
{
	char	*prompt;

	prompt = build_prompt(heap_allocated);
	return (prompt);
}

char	*build_prompt(t_heap_allocated * heap_allocated)
{
	char	*buffer;
	char	*prompt;
	char	*temp;
    t_heap heap;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->tokens;
    buffer = getcwd(NULL, 0);
    temp = buffer;
    if (!buffer)
        buffer = mini_ft_strdup(heap_allocated,heap.list,"FIXME");
    buffer = mini_ft_strdup(heap_allocated,heap.list,buffer);
    free(temp);
    // if (!buffer)
    //     buffer = mini_ft_strdup(heap_allocated,heap_allocated->tokens,_getenv(heap,)) // FIXME To edit once new struct is created to fail safe;
	prompt = last_ocur(buffer, '/');
	prompt = mini_ft_strjoin(heap_allocated, heap_allocated->input,"\1\033[1;34m\2", prompt + 1);
	temp = mini_ft_strjoin(heap_allocated, heap_allocated->input,prompt, "\1\033[0m\2");
    prompt = mini_ft_strjoin(heap_allocated, heap_allocated->input,temp,
			mini_ft_strjoin(heap_allocated,heap_allocated->input,\
    mini_ft_strjoin(heap_allocated,heap_allocated->input," via \1\033[1;34m\2",last_ocur(getenv("SHELL"),'/')+1),"\1\n🦪\2 \1→\2 \1\033[0m\2"));
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
