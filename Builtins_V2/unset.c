/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 02:49:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 18:40:04 by kgriset          ###   ########.fr       */
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

void __index(t_index * index)
{
    index->i = -1;
        index->j = -1;
}

int mini_unset(t_heap * heap, char ** args, char *** envp)
{
    t_index index;
    char ** new_env;
    bool matched;

    index.i = 0;
    index.count = 0;
    new_env = NULL;
    index.count = _count_unset(heap, args, envp, &new_env);
    if (index.count)
    {
        __index(&index);
        while((*envp)[++index.i])
        {
            matched = false; 
            index.count = 0;
            while(args[++index.count])
                if (u_var_name_cmp(args[index.count],(*envp)[index.i]) == 0)
                    matched = true;
            if (matched == false)
                new_env[++index.j] = mini_ft_strdup(heap->heap_allocated, heap->env, (*envp)[index.i]);
        }
        *envp = new_env;
    }
    return (0);
}
