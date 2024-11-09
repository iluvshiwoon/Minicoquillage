/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:32:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/09 19:07:04 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int _count(char ** envp, t_heap * heap, char * str, int status);
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

void _init_expand(char ** envp, t_heap * heap, char ** to_expand, t_expanded * expanded, int status)
{
    int i;
    int count;
    
    i = -1;
    count = 0;
    while (to_expand[++i])
        if (_count(envp, heap, to_expand[i], status))
            count++;
    expanded->value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*to_expand) * (count + 1));
    expanded->value[count] = NULL;
    expanded->litteral = wrap_malloc(heap->heap_allocated, heap->list, sizeof(bool*) * (count + 1));
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

int _expand_sep(char c)
{
    if (c == '\'' || c == '\"' || c == '$')
        return (1); 
    return (0);
}

int _count_exp(char ** envp , t_heap * heap, char * str, int * i, int status)
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
        r_value = _getenv(heap,var, envp, status);
        if (r_value) 
        {
            ++k;
            break;
        }
    }
    if (k-*i == 1 && !_expand_sep(str[k]))
        ++count;
    if (r_value)
        count +=  ft_strlen(r_value); 
    if (var)
        *i += ft_strlen(var);
    return count;
}

char * _assign_exp(char ** envp , t_heap * heap, char * str, int * i, int status)
{
    int k;
    char * r_value;
    char * var;

    k = *i;
    r_value = NULL;
    var = NULL;
    while(str[++k] && !_expand_sep(str[k]))
    {
        var = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*var) * (k-*i + 1));
        ft_strlcpy(var, str+*i+1,(k-*i + 1));
        r_value = _getenv(heap, var, envp, status);
        if (r_value) 
        {
            ++k;
            break;
        }
    }
    if (k-*i == 1 && !_expand_sep(str[k]))
    {
        r_value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * 2);
        r_value[0] = '$';
        r_value[1] = '\0';
    }
    if (var)
        *i += ft_strlen(var);
    return (r_value);
}


int _count(char ** envp, t_heap * heap, char * str, int status)
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
            count += _count_exp(envp, heap, str, &i, status);
        else if (str[i] == '"' && open.double_quote)
            open.double_quote = 0;
        else if (str[i] == '\'' && open.single_quote)
            open.single_quote = 0;
        else
            ++count;
        if (!str[i])
            break;
    }
    return count;
}

void _assign(char ** envp, t_heap * heap, t_expanded * expanded, char ** to_expand, int i, int status)
{
    int j;
    int k;
    int l;
    t_open_quote open;
    bool litteral;
    char * r_value;

    litteral = false;
    open.double_quote = 0;
    open.single_quote = 0;
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
            r_value = _assign_exp(envp, heap, to_expand[i], &j, status); 
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
        if (!to_expand[i][j])
            break;
    }
}

t_expanded * _expand(t_heap * heap, char ** to_expand, char ** envp, int status)
{
    t_expanded * expanded;
    int i;
    int count;

    expanded = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*expanded));
    _init_expand(envp, heap, to_expand, expanded, status);
    i = -1;
    while (to_expand[++i])
    {
        count = _count(envp,heap, to_expand[i], status);
        if (count)
        {
            expanded->litteral[i] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(bool) * (count));
            expanded->value[i] = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * (count + 1));
            expanded->value[i][count] = '\0';
            _assign(envp, heap, expanded, to_expand, i, status);
        }
    }
    return (expanded);
}

int _count_glob(t_heap * heap, char * str, bool * litteral)
{
    int count;  
    t_glob * globbed;
    
    globbed = glob(heap, str, litteral);
    count = 0;
    while(globbed)
    {
        count++;
        globbed = globbed->next;
    }
    return count; 
}

char ** _glob_args(t_heap * heap, t_expanded * expanded)
{
    int i;
    int j;
    int count; 
    char ** r_value;
    t_glob * globbed;

    i = -1;
    count = 0;
    while (expanded->value[++i])
    {
        j = _count_glob(heap, expanded->value[i], expanded->litteral[i]);
        if (j)
            count += j;
        else 
            count++;
    }
    r_value = wrap_malloc(heap->heap_allocated, heap->list, sizeof(*r_value) * (count + 1));
    r_value[count] = NULL;
    i = -1;
    j = -1;
    while (expanded->value[++i])
    {
        globbed = glob(heap, expanded->value[i], expanded->litteral[i]);
        if (globbed)
        {
            while (globbed)
            {
                r_value[++j] = globbed->file; 
                globbed = globbed->next;
            }
        }
        else
        {
            ++j;
            r_value[j] = expanded->value[i];
        }
    }
    return r_value;
}
