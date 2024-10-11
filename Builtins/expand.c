#include "./builtins.h"


int is_quote(int in_quote, char c, char *content)
{
	int	i;

	i = 0;
	if (content[i] == c)
	{
		while (content[++i])
		{
			if (content[i] == c)
				return (i);
		}
	}
	return (0);
}

void	ft_fill_noexpand(t_expand *expand_list, char *content, char **env)
{
	t_expand	*new_expand;
	t_expand	*tmp;

	new_expand = malloc(sizeof(t_expand));
	new_expand->content = content;
	new_expand->next = NULL;
	tmp = expand_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_expand;
}

void	add_expand_list(t_expand *expand_list, char *content)
{
	new_expand = malloc(sizeof(t_expand));
	new_expand->content = content;
	new_expand->next = NULL;
	tmp = expand_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_expand;
}

void	ft_fill_expand(t_expand *expand_list, char *content, char **env)
{
	t_expand	*new_expand;
	char		*expanded_content;
	int			i;
	int			j;

	i = 0;
	while (content[i])
	{
		j = 0;
		if (content[i] == '$')
		{
			i++;
			while (content[i + j] != ' ' && content[i + j] != 0 && content[i + j] != '\n')
				j++;
			expanded_content = ft_substr(content, i, j);
			add_expand_list(expand_list, expanded_content);
		}
		else
		{
			while (content[i+j] != '$' && content[i+j] != 0)
				j++;
			expanded_content = ft_substr(content, i, j);
			add_expand_list(expand_list, expanded_content);
		}
	}
}

t_expand	ft_expand(char *content, char **env)
{
	int			i;
	int			j;
	t_expand	*expand_list;
	t_expand	*res;
	char		*sample_sentence;

	expand_list = malloc(sizeof(t_expand));
	expand_list->content = NULL;
	expand_list->next = NULL;
	i = 0;
	j = 0;
	res = expand_list;
	while (content[i])
	{
		j = 0;
		if (content[i] == '\'')
		{
			j = is_quote(j, '\'', content + i);
			sample_sentence = ft_substr(content, i, j);
			ft_fill_noexpand(expand_list, sample_sentence, env);
			free(sample_sentence);
			i += j;
		}
		else if (content[i] == '\"')
		{
			j = is_quote(j, '\"', content + i);
			sample_sentence = ft_substr(content, i, j);
			ft_fill_expand(expand_list, sample_sentence, env);
			free(sample_sentence);
			i += j;
		}
		else
		{
			while (content[i+j] != 0 && content[i+j] != '\'' && content[i+j] != '\"')
				j += 1;
			sample_sentence = ft_substr(content, i, j);
			ft_fill_expand(expand_list, sample_sentence, env);
			i += j;
		}
		i++;
	}
	return (expand_list);
}
