/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:37:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 11:57:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

bool is_dir(char * cmd)
{
    struct stat statbuf;

    if (stat(cmd, &statbuf) != 0)
        return 0;
    if (S_ISDIR(statbuf.st_mode))
        return (ft_printf_fd(STDERR_FILENO,"minicoquillage: %s: Is a directory\n",cmd),1);
    return 0;
}

static bool is_path(char * cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
        if (cmd[i] == '/')
            return(true);
    return (false);
}

bool check_builtin(t_heap* heap, char * cmd)
{
    char ** split;
    char * builtin;
    int i;

    i = -1;
    builtin = "echo,cd,pwd,export,unset,env,exit";
    if (!cmd)
        return (false);
    split = mini_ft_split(heap, builtin, ',');
    while (split[++i])
        if (ft_strncmp(cmd, split[i],_max_len(ft_strlen(cmd),ft_strlen(split[i]))) == 0)
            return (true);
    return (false);
}

char * get_path(t_heap * heap,char ** envp,int * status, char * cmd)
{
    char ** path;
    char * r_value;
    int i;

    i = -1; 
    r_value = _getenv(heap, "PATH", envp, *status);
    if (!r_value)
        return (*status = 127,ft_printf_fd(STDERR_FILENO,"%s",mini_ft_strjoin(heap->heap_allocated,heap->list,mini_ft_strjoin(heap->heap_allocated,heap->list,"minicoquillage: ",cmd),": No such file or directory\n")),NULL);
    path = mini_ft_split(heap,r_value, ':');
    if (!cmd)
        return (NULL);
    if (!(cmd[0]))
        return(*status = 127,ft_printf_fd(STDERR_FILENO,"minicoquillage: %s",mini_ft_strjoin(heap->heap_allocated,heap->list,cmd,": command not found\n")),NULL);
    if (is_path(cmd) && access(cmd, F_OK) == -1)
        return (*status = 127,ft_printf_fd(STDERR_FILENO,"%s",mini_ft_strjoin(heap->heap_allocated,heap->list,mini_ft_strjoin(heap->heap_allocated,heap->list,"minicoquillage: ",cmd),": No such file or directory\n")),NULL);
    else if (is_path(cmd) && access(cmd, X_OK) == -1)
        return(*status = 126,ft_printf_fd(STDERR_FILENO,"minicoquillage: %s: Permission denied\n",cmd),NULL);
    else if (is_path(cmd) && is_dir(cmd))
        return (*status = 126,NULL);
    else if (is_path(cmd) && access(cmd, X_OK) == 0)
        return (cmd);
    while (path[++i])
    {
        r_value = ft_strnstr(path[i], cmd, ft_strlen(path[i]));
        if (r_value && r_value != path[i] && !*(r_value + ft_strlen(cmd)))
        {
            if (access(path[i], X_OK) == 0)
                return (path[i]);
            return(*status = 126,ft_printf_fd(STDERR_FILENO,"minicoquillage: %s: Permission denied\n",path[i]),NULL);
        }
    }
    i = -1;
    while (path[++i])
    {
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, path[i], "/");
        r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, r_value, cmd);
        if (access(r_value, F_OK) == 0)
        {
            if (is_dir(r_value))
                return (*status = 126,NULL);
            else if (access(r_value, X_OK) == 0)
                return (/* *status = 126,  */r_value);
            return(*status = 126,ft_printf_fd(STDERR_FILENO,"minicoquillage: %s: Permission denied\n",r_value),NULL);
        }
    }
    return(*status = 127,ft_printf_fd(STDERR_FILENO,"minicoquillage: %s",mini_ft_strjoin(heap->heap_allocated,heap->list,cmd,": command not found\n")),NULL);
    // return(*status = 127,ft_putstr_fd("command not found\n",STDERR_FILENO),NULL);
}
