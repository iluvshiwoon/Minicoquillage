/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:59:54 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/21 20:14:29 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int _var_name_cmp(char * s1, char * s2)
{
    int i;
    i = -1;
    while (s1[++i] != '=' && s2[i] != '=')
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    return (s1[i] - s2[i]);
}

int _search_var(t_heap * heap, char * arg, char ** env)
{
    int i;

    i = -1;
    while (env[++i])
    {
        if (_var_name_cmp(env[i], arg) == 0)
        {
            env[i] = mini_ft_strdup(heap->heap_allocated,heap->env,arg);
            return (0);
        }
    }
    return (1);
}

int _check_var(char * var, bool print)
{
    int i;
    int r_value;

    i = -1;
    r_value = 0;
    while (var[++i])
    {
        if (var[i] == '=')
            break;
        if (i==0 && ft_isdigit(var[i]))
            r_value = 1;
        else if (!ft_isalnum(var[i]) && var[i] != '_')
            r_value = 1;
    }
    if (var[i] == '\0')
    {
        if (r_value == 0 && i)
            print = false;
        r_value = 1;
    }
    else if (var[i] == '=' && i == 0)
        r_value = 1;
    if (r_value && print)
        return(ft_printf_fd(STDERR_FILENO,"minicoquillage: export: `%s': not a valid identifier\n",var),2);
    return (r_value);
}

size_t _count_export(t_heap * heap,char ** args, char *** envp, char *** new_env)
{
    int i;
    int j;
    size_t count;

    i = -1;
    j = 0;
    count = 0;
    while ((*envp)[++i]);
    while (args[++j])
        if (_check_var(args[j], false) == 0 && _search_var(heap,args[j],*envp))
            count++;
    if (count != 0)
    {
        count += i + 1;
        *new_env = wrap_malloc(heap->heap_allocated, heap->env, sizeof(**new_env)*count);
        (*new_env)[count - 1] = NULL;
    }
    return (count);
}

int mini_export(t_heap * heap, char ** args, char *** envp)
{
    int i; 
    int r_value;
    size_t count;
    char ** new_env;

    i = 0;
    r_value = 0;
    count = 0;
    new_env = NULL;
    while (args[++i])
        if (_check_var(args[i], true) == 2)
            r_value = 1;
    count = _count_export(heap, args, envp, &new_env);
    if (count)
    {
        i = -1;
        while((*envp)[++i])
            new_env[i] = mini_ft_strdup(heap->heap_allocated, heap->env,(*envp)[i]); 
        count = 0;
        while(args[++count])
            if (_check_var(args[count], false) == 0)
                new_env[i++] = mini_ft_strdup(heap->heap_allocated, heap->env,args[count]);
        *envp = new_env;
    }
    return(r_value);
}
