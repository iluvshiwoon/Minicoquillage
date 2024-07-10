/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokens3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:06:44 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/10 16:56:49 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

int	expand(size_t *j, char **value, char **temp,
		t_double_link_node **node)
{
	t_token	*token;
    size_t len;

	token = (*node)->data;
    len = ft_strlen(token->value);
	*temp = expand_expand(*j, *value);
    while ((*value)[*j] && (*value)[*j] != '"' && (*value)[*j] != '\'' && !ft_sep((*value)[*j]))
        ++(*j);
	free(*value);
	token->value = *temp;
	*value = *temp;
	(*j) = *j + ft_strlen(*value) - len - 1;

	return (0);
}

char	*expand_expand(size_t j, char *token)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	size_t	index;

	index = j;
	while (token[j] && token[j] != '"' && token[j] != '\'' && !ft_sep(token[j]))
        ++j;
	temp = malloc(sizeof(char) * (j - index + 1));
	temp3 = malloc(sizeof(char) * (index + 1));
	ft_strlcpy(temp3, token, index + 1);
	ft_strlcpy(temp, token + index, j - index + 1);
    temp2 = expand_var(temp);
    free(temp);
    temp = temp2;
	temp2 = ft_strjoin(temp3, temp);
	free(temp3);
    free(temp);
	temp = ft_strjoin(temp2, token + j);
	free(temp2);
	return (temp);
}

int	expand_expand_all(size_t *j, char **value)
{
    size_t len;
    char * temp;

    len = ft_strlen(*value);
	temp = expand_expand(*j, *value);
    while ((*value)[*j] && (*value)[*j] != '"' && (*value)[*j] != '\'' && !ft_sep((*value)[*j]))
        ++(*j);
    free(*value);
    *value = temp;
	(*j) = *j + ft_strlen(*value) - len - 1;

	return (0);
}

char * expand_all(char * str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            expand_expand_all(&i, &str);
        ++i;
    }
    return (str);
}

char * expand_var(char * str)
{
    size_t i;
    size_t j;
    char * var;
    char * var_name;
    char * temp;
    char * temp1;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '$')
        ++i;
    if (!str[i])
        return (ft_strdup(str));
    j = i;
    while (str[j] && str[j] != '"' && str[j] != '\'' && !ft_sep(str[j]))
        ++j;
    if (j - i == 1)
        return (ft_strdup(str));
    var_name = malloc(sizeof(char) * (j - i));
    ft_strlcpy(var_name, str + i + 1, j - i);
    var = getenv(var_name);
    if (!var)
        var = (char *){""};
    temp = malloc(sizeof(char) * (i + 1));
    ft_strlcpy(temp, str, i + 1);
    temp1 = ft_strjoin(temp, var);
    free(temp);
    temp = ft_strjoin(temp1, str + j);
    free(temp1);
    return (free(var_name),temp);
}
