/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:31:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 00:14:17 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

char * var_name(t_heap * heap, char * var)
{
    int i;
    char * name;
    i = -1;
    while (var[++i] != '=');
    name = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*name) * (i + 1));
    name[i] = '\0';
    i = -1;
    while (var[++i] != '=')
        name[i] = var[i];
    return name;
}

char * _getenv(t_heap * heap, char * var, char ** envp, int status)
{
    int i;
    char * name;

    i = -1;
    if (!envp)
        return (NULL);
    if (!ft_strncmp("?",var,_max_len(ft_strlen(var), 1)))
        return (mini_ft_itoa(heap, status));
    while (envp[++i])
    {
        name = var_name(heap, envp[i]);
        if(!ft_strncmp(name, var, _max_len(ft_strlen(name),ft_strlen(var))))
            return (envp[i] + ft_strlen(name) + 1);
    }
    return (NULL);
}

bool _is_empty_quote(t_mini * mini, char * to_expand)
{
    int count;
    int i;
    t_to_expand _expand;

    _expand.open.double_quote =1;
    _expand.status = 0;
    count = 1;
    i = 1;
    if (to_expand[0] == '\'' || to_expand[0] == '"')
    {
        if (to_expand[1] == to_expand[0])
            return true;
        else if (to_expand[1] == '$')
        {
            count = _count_exp(mini, to_expand, &i,_expand);
            if (count == 0 && to_expand[i+1] == to_expand[0] && to_expand[i+2] == 0) 
                return true;
        }
    }    
    return false;
}

void _init_expand(t_mini * mini, char ** to_expand, t_expanded * expanded, int status)
{
    int i;
    int count;
    
    i = -1;
    count = 0;
    while (to_expand[++i])
        if (_count(mini, to_expand[i], status) ||\
_is_empty_quote(mini,to_expand[i]))
            count++;
    expanded->value = wrap_malloc(&mini->heap_allocated, mini->heap.list,\
sizeof(*to_expand) * (count + 1));
    expanded->value[count] = NULL;
    expanded->litteral = wrap_malloc(&mini->heap_allocated, mini->heap.list,\
sizeof(bool*) * (count + 1));
    expanded->litteral[count] = NULL;
}

int	_handle_quote(char c, t_open_quote *open)
{
	if (c == '"' && !open->single_quote
		&& !open->double_quote)
	{
		open->double_quote = 1;
		return (EXIT_SUCCESS);
	}
	else if (c == '\'' && !open->single_quote
		&& !open->double_quote)
	{
		open->single_quote = 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
