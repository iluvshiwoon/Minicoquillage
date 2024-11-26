/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:11 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 11:21:40 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void mini_write(t_heap * heap,int fd, char * str, ssize_t bytes)
{
    ssize_t written;
    size_t offset;

    written = 0;
    offset = 0;
    while(1)
    {
        written = write(fd, str + offset, bytes - offset);
        if (written == -1)
            return(perror(NULL),error_exit("write failed\n",heap->heap_allocated));
        if (written == bytes)
            break;
        offset = written;
    }
}

size_t _max_len(size_t len1, size_t len2)
{
    if (len1 >= len2)
        return (len1);
    return (len2);
}

void    _write_listen(t_heap * heap, int fd, char * line)
{
    mini_write(heap, fd, line, ft_strlen(line));
    mini_write(heap, fd, "\n", 1);
}
