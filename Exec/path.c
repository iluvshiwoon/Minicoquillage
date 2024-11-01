/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:37:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/01 15:25:38 by kgriset          ###   ########.fr       */
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
        if (ft_strncmp(cmd, split[i],_max_len(ft_strlen(cmd),ft_strlen(split[i]))) == 0)// FIXME issue here
            return (true);
    return (false);
}

char * get_path(t_heap * heap,int * status, char * cmd)
{
    char ** path;
    char * r_value;
    int i;

    i = -1;
    path = mini_ft_split(heap, getenv("PATH"), ':');
    if (!heap || !cmd)
        return(printf("Wrong use of get_path\n"),NULL);
    if (check_builtin(heap, cmd))// put in _exec_tree
        return(printf("%s",mini_ft_strjoin(heap->heap_allocated, heap->list, cmd, ": shell built-in command\n")),NULL);
    if (is_path(cmd) && access(cmd, F_OK) == -1)
        return (*status = 127,printf("%s",mini_ft_strjoin(heap->heap_allocated,heap->list,mini_ft_strjoin(heap->heap_allocated,heap->list,"Minicoquillage: ",cmd),": No such file or directory\n")),NULL);
    else if (is_path(cmd) && access(cmd, X_OK) == -1)
        return(*status = 126,printf("minicoquillage: Permission denied\n"),NULL);
    else if (is_path(cmd) && access(cmd, X_OK) == 0)
        return (cmd);
    while (path[++i])
    {
        r_value = ft_strnstr(path[i], cmd, ft_strlen(path[i]));
        if (r_value && r_value != path[i] && !*(r_value + ft_strlen(cmd)))
        {
            if (access(path[i], X_OK) == 0)
                return (path[i]);
            return(*status = 126,printf("minicoquillage: Permission denied\n"),NULL);
        }
    }
    i = -1;
    while (path[++i])
    {
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, path[i], "/");
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, r_value, cmd);
        if (access(r_value, F_OK) == 0)
        {
            if (access(r_value, X_OK) == 0)
                return (r_value);
            return(*status = 126,printf("minicoquillage: Permission denied\n"),NULL);
        }
    }
    return(*status = 127,printf("%s",mini_ft_strjoin(heap->heap_allocated,heap->list,cmd,": command not found\n")),NULL);
}
