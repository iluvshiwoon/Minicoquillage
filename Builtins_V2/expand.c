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


void	add_expand_list(t_expand *expand_list, char *content)
{
	t_expand	*new_expand;
	t_expand	*tmp;

	new_expand = malloc(sizeof(t_expand));
	if (new_expand == NULL)
		return ;
	new_expand->content = content;
	new_expand->next = NULL;
	tmp = expand_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_expand;
}

void	ft_fill_noexpand(t_expand *expand_list, char *content, char **env)
{

}

void	ft_fill_expand(t_expand *expand_list, char *content, char **env)
{
	t_expand	*new_expand;
	char		*expanded_content;
	int			i;
	int			j;
	t_mylist	*env_list;

	i = 0;
	env_list = ft_env(env);
	while (content[i])
	{
		j = 0;
		if (content[i] == '$')
		{
			i++;
			while (content[i + j] != ' ' && content[i + j] != 0 && content[i + j] != '\n')
				j++;
			expanded_content = ft_substr(content, i, j);
			while (env_list)
			{
				if (ft_strncmp(env_list->var, expanded_content, ft_strlen(env_list->var)) == 0)
				{
					free (expanded_content);
					expanded_content = ft_strdup(env_list->val);
					break ;
				}
				env_list = env_list->next;
			}
			add_expand_list(expand_list, expanded_content);
			i += j;
		}
		else
		{

			while (content[i+j] != '$' && content[i+j] != 0)
				j++;
			expanded_content = ft_substr(content, i, j);
			add_expand_list(expand_list, expanded_content);
			i += j;
		}
	}
}

t_expand	*ft_expand(char *content, char **env)
{
	int			i;
	int			j;
	t_expand	*expand_list;
	t_expand	*res;
	char		*sample_sentence;

	expand_list = malloc(sizeof(t_expand));
	if (expand_list == NULL)
		return (NULL);
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
			add_expand_list(expand_list, sample_sentence);
			// ft_fill_noexpand(expand_list, sample_sentence, env);
			free(sample_sentence);
			i += j + 1;
		}
		else if (content[i] == '\"')
		{
			j = is_quote(j, '\"', content + i);
			sample_sentence = ft_substr(content, i, j);
			ft_fill_expand(expand_list, sample_sentence, env);
			free(sample_sentence);
			i += j + 1;
		}
		else
		{
			while (content[i+j] != 0 && content[i+j] != '\'' && content[i+j] != '\"')
				j += 1;
			sample_sentence = ft_substr(content, i, j + 1);
			ft_fill_expand(expand_list, sample_sentence, env);
			free(sample_sentence);
			i += j;
		}
		i++;
	}
	return (res);
}


