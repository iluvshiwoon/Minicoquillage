/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:32:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/06 18:58:39 by kgriset          ###   ########.fr       */
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

char * _getenv(t_heap * heap, char * var, char ** envp)
{
    int i;
    char * name;

    i = -1;
    while (envp[++i])
    {
        name = var_name(heap, envp[i]);
        if(!ft_strncmp(name, var, _max_len(ft_strlen(name),ft_strlen(var))))
            return (envp[i] + ft_strlen(name) + 1);
    }
    return (NULL);
}

void _init_expand(t_heap * heap, char ** to_expand, char *** value, bool *** litteral)
{
    int i;
    
    i = -1;
    while (to_expand[++i]);
    *value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*to_expand) * (i + 1));
    (*value)[i] = NULL;
    *litteral = wrap_malloc(heap->heap_allocated, heap->list, sizeof(**litteral) * (i + 1));
    (*litteral)[i] = NULL;
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

int _expand_sep(char c)
{
    if (c == '\'' || c == '\"' || c == '$')
        return (1); 
    return (0);
}

int _count_exp(char ** envp , t_heap * heap, char * str, int * i)
{
    int k;
    int count;
    char * r_value;
    char * var;

    k = *i;
    count = 0;
    var = NULL;
    while(str[++k] && !_expand_sep(str[k]))
    {
        var = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*var) * (k-*i + 1));
        ft_strlcpy(var, str+*i+1,(k-*i + 1));
        r_value = _getenv(heap,var, envp);
        if (r_value) 
        {
            ++k;
            break;
        }
    }
    if (k-*i == 1 && _expand_sep(str[k]))
        ++count;
    if (r_value)
        count +=  ft_strlen(r_value); 
    *i += k-1;
    return count;
}

char * _assign_exp(char ** envp , t_heap * heap, char * str, int * i)
{
    int k;
    char * r_value;
    char * var;

    k = *i;
    r_value = NULL;
    while(str[++k] && !_expand_sep(str[k]))
    {
        var = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*var) * (k-*i + 1));
        ft_strlcpy(var, str+*i+1,(k-*i + 1));
        r_value = _getenv(heap, var, envp);
        if (r_value) 
        {
            ++k;
            break;
        }
    }
    if (k-*i == 1 && _expand_sep(str[k]))
    {
        r_value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * 2);
        r_value[0] = '$';
        r_value[1] = '\0';
    }
    *i += k-1;
    return (r_value);
}


int _count(char ** envp, t_heap * heap, char * str)
{
    int i;
    int count;
    t_open_quote open;

    i = -1;
    count = 0;
    open.double_quote = 0;
    open.single_quote = 0;
    while(str[++i])
    {
        if (_handle_quote(str[i], &open) == EXIT_SUCCESS);
        else if (str[i] == '$' && !open.single_quote)
            count += _count_exp(envp, heap, str, &i);
        else if (str[i] == '"' && open.double_quote)
            open.double_quote = 0;
        else if (str[i] == '\'' && open.single_quote)
            open.single_quote = 0;
        else
            ++count;
    }
    return count;
}

void _assign(char ** envp, t_heap * heap, t_expanded * expanded, char ** to_expand, int i)
{
    int count;
    int j;
    int k;
    int l;
    t_open_quote open;
    bool litteral;
    char * r_value;

    litteral = false;
    open.double_quote = 0;
    open.single_quote = 0;
    count = _count(envp,heap, to_expand[i]);
    expanded->litteral[i] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(bool) * (count));
    expanded->value[i] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * (count + 1));
    expanded->value[i][count] = '\0';
    j = -1;
    l = 0;
    while (to_expand[i][++j])
    {
        if (_handle_quote(to_expand[i][j], &open) == EXIT_SUCCESS)
            litteral = true;
        else if (to_expand[i][j] == '$' && !open.single_quote)
        {
            litteral = false;
            k = -1;
            r_value = _assign_exp(envp, heap, to_expand[i], &j); 
            if (r_value)
            {
                while(r_value[++k])
                {
                    expanded->litteral[i][l] = litteral;
                    expanded->value[i][l++] = r_value[k]; 
                }
            }
        }
        else if (to_expand[i][j] == '"' && open.double_quote)
        {
            litteral = false;
            open.double_quote = 0;
        }
        else if (to_expand[i][j] == '\'' && open.single_quote)
        {
            litteral = false;
            open.single_quote = 0;
        }
        else
        {
            expanded->litteral[i][l] = litteral;
            expanded->value[i][l++] = to_expand[i][j];
        }
    }
}

t_expanded * _expand(t_heap * heap, char ** to_expand, char ** envp)
{
    t_expanded * expanded;
    int i;

    expanded = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*expanded));
    _init_expand(heap, to_expand, &expanded->value, &expanded->litteral);
    i = -1;
    while (to_expand[++i])
        _assign(envp, heap, expanded, to_expand, i);
    return (expanded);
}
