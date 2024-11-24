/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 02:49:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/24 23:43:44 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int u_var_name_cmp(char * arg, char * env)
{
    int i;
    i = -1;
    if (!arg || !arg[0] || !env)
        return (42);
    while (env[++i] != '=');
    if (ft_strncmp(arg,env,_max_len(ft_strlen(arg),i)) == 0)
        return (0);
    return (1);
    // while (arg[++i] && env[i] != '=')
    //     if (arg[i] != env[i] && !(arg[i] == '\0' && env[i] == '='))
    //         return (arg[i] - env[i]);
    // if (i)
    //     i--;
    // return (arg[i] - env[i]);
}

int unset_search_var(char * arg, char ** env)
{
    int i;

    i = -1;
    while (env[++i])
    {
        if (u_var_name_cmp(arg, env[i]) == 0)
            return (0);
    }
    return (1);
}

size_t _count_unset(t_heap * heap,char ** args, char *** envp, char *** new_env)
{
    int i;
    int j;
    size_t count;

    i = -1;
    j = 0;
    count = 0;
    while ((*envp)[++i]);
    while (args[++j])
        if (unset_search_var(args[j],*envp) == 0)
            count++;
    if (count != 0)
    {
        count = i - count;
        *new_env = wrap_malloc(heap->heap_allocated, heap->env, sizeof(**new_env)*(count + 1));
        (*new_env)[count] = NULL;
    }
    return (count);
}

int mini_unset(t_heap * heap, char ** args, char *** envp)
{
    int i; 
    int j;
    size_t count;
    char ** new_env;
    bool matched;

    i = 0;
    count = 0;
    new_env = NULL;
    count = _count_unset(heap, args, envp, &new_env);
    if (count)
    {
        i = -1;
        j = -1;
        while((*envp)[++i])
        {
            matched = false; 
            count = 0;
            while(args[++count])
                if (u_var_name_cmp(args[count],(*envp)[i]) == 0)
                    matched = true;
            if (matched == false)
                new_env[++j] = mini_ft_strdup(heap->heap_allocated, heap->env, (*envp)[i]);
        }
        *envp = new_env;
    }
    return (0);
}
