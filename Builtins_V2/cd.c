/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:56:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/16 05:58:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
    char * temp;

    home = _getenv(heap, "HOME", *envp, 0);
    if (!home)
    {
        home = _getenv(heap, "USER", *envp, 0);
        if (!home)
        {
            temp = getcwd(NULL, 0);
            home = mini_ft_strdup(heap->heap_allocated, heap->list, temp);
            free(temp);
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

    i = chdir(path);
    if (i != 0)
        return (printf("minicoquillage: cd: %s: %s\n",path,strerror(errno)),1);
    cur_dir = _getenv(heap, "PWD", *envp, 0);
    f_export(heap, envp, "OLDPWD=", cur_dir);
    cur_dir = getcwd(NULL, 0);
    f_export(heap, envp, "PWD=", mini_ft_strdup(heap->heap_allocated, heap->list, cur_dir));
    free(cur_dir);
    return (0);
}

int mini_cd(t_heap * heap, char ** args, char *** envp)
{
    int i;
    char * path;

    i = 0;
    path = args[1];
    while (args[++i]);
    if (i > 2)
        return (printf("minicoquillage: cd: too many arguments\n"),1);
    if (args[1] == NULL || ft_strncmp(args[1], "~", _max_len(ft_strlen(args[1]),1)) == 0)
        path = get_home(heap, envp);
    else if (ft_strncmp(args[1],"-", _max_len(ft_strlen(args[1]),1)) == 0)
    {
        path = _getenv(heap, "OLDPWD", *envp, 0);
        printf("%s\n",path);
    }
    return(_cd(heap, path, envp));
}
