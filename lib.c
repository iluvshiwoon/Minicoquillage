/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:13:18 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:04:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void m_pipe(t_mini *mini, int (**pipefd)[2], int i)
{
    // int *fd;
    // t_double_link_node * node;

	if (pipe((*pipefd)[i]) == -1)
        return(close_fds(mini->fds),free_heap(mini,true),ft_printf_fd(STDERR_FILENO,"minicoquillage: pipe: %s\n",strerror(errno)),exit(42));
    // node = wrap_malloc(mini,  sizeof(*node));
    // fd = wrap_malloc(mini,  sizeof(*fd));
    // node->data = fd;
    // *fd = (*pipefd)[i][0];
    // mini->fds->pf_insert_end(mini->fds,node);
    // node = wrap_malloc(mini,  sizeof(*node));
    // fd = wrap_malloc(mini,  sizeof(*fd));
    // node->data = fd;
    // *fd = (*pipefd)[i][1];
    // mini->fds->pf_insert_end(mini->fds,node);
}

int m_open(t_mini *mini, const char *pathname, int flags, mode_t mode)
{
    int *fd;
    t_double_link_node *node;

    node = wrap_malloc(mini,  sizeof(*node));
    fd = wrap_malloc(mini,  sizeof(*fd));
    node->data = fd;
    if (mode)
        *fd = open(pathname, flags, mode);
    else
        *fd = open(pathname, flags);
    if (*fd == -1 && errno != ENOENT)
        return(close_fds(mini->fds),free_heap(mini, true),ft_printf_fd(STDERR_FILENO, "minicoquillage: open: %s\n", strerror(errno)), exit(42),0);
    mini->fds->pf_insert_end(mini->fds, node);
    return (*fd);
}

void    m_dup2(t_mini * mini, int fd1, int std)
{
    int r;
    r = dup2(fd1, std);
    if (r == -1)
        return(close_fds(mini->fds),free_heap(mini, true),ft_printf_fd(STDERR_FILENO, "minicoquillage: dup2: %s\n", strerror(errno)), close(std),exit(42));
}

int m_dup(t_mini * mini, int std)
{
    int *fd;
    t_double_link_node *node;

    node = wrap_malloc(mini,  sizeof(*node));
    fd = wrap_malloc(mini,  sizeof(*fd));
    node->data = fd;
    *fd = dup(std);
    if (*fd == -1)
        return(close_fds(mini->fds), free_heap(mini, true),ft_printf_fd(STDERR_FILENO, "minicoquillage: dup: %s\n", strerror(errno)),close(std),exit(42),0);
    mini->fds->pf_insert_end(mini->fds, node);
    return (*fd);
}
