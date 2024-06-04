/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:39:04 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/04 16:29:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

size_t	skip_space(char *line, size_t index)
{
	if (!line[index])
		return (index);
	while (ft_isspace(line[index]) && ft_isspace(line[index + 1]))
		++index;
	return (index);
}

char	*expand_double(size_t j, char *token)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	size_t	index;

	index = j - 1;
	while (token[index] != '"')
		--index;
	temp = malloc(sizeof(char) * (j - index));
	temp3 = malloc(sizeof(char) * (index + 1));
	ft_strlcpy(temp3, token, index + 1);
	ft_strlcpy(temp, token + index + 1, j - index);
	temp2 = ft_strjoin(temp3, temp);
	free(temp3);
	free(temp);
	temp = ft_strjoin(temp2, token + j + 1);
	free(temp2);
	return (temp);
}

char	*expand_single(size_t j, char *token)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	size_t	index;

	index = j - 1;
	while (token[index] != '\'')
		--index;
	temp = malloc(sizeof(char) * (j - index));
	temp3 = malloc(sizeof(char) * (index + 1));
	ft_strlcpy(temp3, token, index + 1);
	ft_strlcpy(temp, token + index + 1, j - index);
	temp2 = ft_strjoin(temp3, temp);
	free(temp3);
	free(temp);
	temp = ft_strjoin(temp2, token + j + 1);
	free(temp2);
	return (temp);
}

int	expand_single_quote(size_t *j, char **value, char **temp,
		t_double_link_node **node)
{
    t_token * token;

    token = (*node)->data;
	*temp = expand_single(*j, *value);
	free(*value);
	token->value = *temp;
	*value = *temp;
	(*j) -= 2;
	return (0);
}

int	expand_double_quote(size_t *j, char **value, char **temp,
		t_double_link_node **node)
{
    t_token * token;

    token = (*node)->data;
	*temp = expand_double(*j, *value);
	free(*value);
	token->value = *temp;
	*value = *temp;
	(*j) -= 2;
	return (0);
}
