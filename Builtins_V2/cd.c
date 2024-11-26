/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:56:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 00:23:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

char * wrap_getcwd(t_heap * heap)
{
    char * r_value;
    char * temp;

    r_value = getcwd(NULL, 0);
    if (!r_value)
        return (printf("error retrieving current directory: getcwd: cannot access parent directories: %s\n",strerror(errno)),NULL);
    temp = r_value; 
    r_value = mini_ft_strdup(heap->heap_allocated, heap->list, r_value);
    free(temp);
    return (r_value);
}

void f_export(t_heap * heap, char *** envp, char * var, char * value)
{
    char ** f_args;

    f_args = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*f_args) * 3);
    f_args[0] = "prout";
    f_args[1] = mini_ft_strjoin(heap->heap_allocated, heap->list, var, value);
    f_args[2] = NULL;
    mini_export(heap, f_args, envp);
}

char * get_home(t_heap * heap, char ***envp)
{
    char * home;

    home = _getenv(heap, "HOME", *envp, 0);
    if (!home)
    {
        home = _getenv(heap, "USER", *envp, 0);
        if (!home)
        {
            home = wrap_getcwd(heap);
            if (!home)
                return NULL;
        }
        else
            home = mini_ft_strjoin(heap->heap_allocated, heap->list, "/home/", home);
    }
    return (home);
}

int _cd(t_heap * heap, char * path, char *** envp)
{
    int i;
    char * cur_dir;

    if (!path)
        return (1);
    i = chdir(path);
    if (i != 0)
        return (printf("minicoquillage: cd: %s: %s\n",path,strerror(errno)),1);
    cur_dir = _getenv(heap, "OLDPWD", *envp, 0);
    if (cur_dir)
    {
        cur_dir = _getenv(heap, "PWD", *envp, 0);
        if (cur_dir)
            f_export(heap, envp, "OLDPWD=", cur_dir);
    }
    cur_dir = _getenv(heap, "PWD", *envp, 0);
    if (cur_dir)
    {
        cur_dir = wrap_getcwd(heap);
        if (cur_dir)
            f_export(heap, envp, "PWD=", mini_ft_strdup(heap->heap_allocated, heap->list, cur_dir));
    }
    return (0);
}

void __print_cd(char ** path, t_heap * heap, char ** envp)
{
    (*path) = _getenv(heap, "OLDPWD", envp, 0);
    if (!(*path))
    {
        (*path) = NULL;
        printf("minicoquillage: cd: OLDPWD not set\n");
    }
    else
    printf("%s\n",(*path));
}

int mini_cd(t_heap * heap, char ** args, char *** envp)
{
    int i;
    char * path;
    char * home;

    i = 0;
    path = args[1];
    while (args[++i]);
    if (i > 2)
        return (printf("minicoquillage: cd: too many arguments\n"),1);
    if (args[1] == NULL)
        path = get_home(heap, envp);
    else if (args[1][0] == '~')
    {
        home = get_home(heap, envp);
        if (home)
            path = mini_ft_strjoin(heap->heap_allocated,heap->list,home,path+1);
    }
    else if (ft_strncmp(args[1],"-", _max_len(ft_strlen(args[1]),1)) == 0)
        __print_cd(&path,heap,*envp);
    return(_cd(heap, path, envp));
}
