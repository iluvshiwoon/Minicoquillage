/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:37:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/26 00:00:01 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

static bool is_path(char * cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
        if (cmd[i] == '/')
            return(true);
    return (false);
}

static bool check_builtin(t_heap* heap, char * cmd)
{
    char ** split;
    char * builtin;
    int i;

    i = -1;
    builtin = "echo,cd,pwd,export,unset,env,exit";
    split = mini_ft_split(heap, builtin, ',');
    while (split[++i])
        if (ft_strncmp(cmd, split[i],ft_strlen(cmd)) == EXIT_SUCCESS)
            return (true);
    return (false);
}

char * get_path(t_heap * heap, char * cmd)
{
    char ** path;
    char * r_value;
    int i;

    i = -1;
    path = mini_ft_split(heap, getenv("PATH"), ':');
    if (!heap || !cmd)
        return(printf("Wrong use of get_path\n"),NULL);
    if (check_builtin(heap, cmd))
        return(printf("%s",mini_ft_strjoin(heap->heap_allocated, heap->list, cmd, ": shell built-in command\n")),NULL);
    if (is_path(cmd) && access(cmd, F_OK) == EXIT_SUCCESS)
        return (cmd);
    else if (is_path(cmd) && access(cmd, F_OK) != EXIT_SUCCESS)
        return (printf("%s",mini_ft_strjoin(heap->heap_allocated,heap->list,mini_ft_strjoin(heap->heap_allocated,heap->list,"Minicoquillage: ",cmd),": No such file or directory\n")),NULL);
    while (path[++i])
    {
        r_value = ft_strnstr(path[i], cmd, ft_strlen(path[i]));
        if (r_value && r_value != path[i] && !*(r_value + ft_strlen(cmd)))
            return (path[i]);
    }
    i = -1;
    while (path[++i])
    {
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, path[i], "/");
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, r_value, cmd);
        if (access(r_value, F_OK) == EXIT_SUCCESS)
            return (r_value);
    }
    return(printf("%s",mini_ft_strjoin(heap->heap_allocated,heap->list,cmd,": command not found\n")),NULL);
}
