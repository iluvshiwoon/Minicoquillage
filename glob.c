/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 03:44:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	put_glob(t_glob *head, int fd)
{
	t_glob	*tmp;
	char	*str;

	tmp = head;
	while (tmp != NULL)
	{
		str = (char *)tmp->file;
		ft_putstr_fd(str, fd);
		if (tmp->next != NULL)
			ft_putchar_fd(' ', fd);
		tmp = tmp->next;
	}
}

char	**store_tmp(t_mini *mini, int size)
{
	const char		*path;
	DIR				*dir;
	struct dirent	*entry;
	char			**tmp;

	tmp = wrap_malloc(mini, sizeof(char *) * (size + 1));
	path = ".";
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		*tmp = mini_ft_strdup(mini, entry->d_name);
		tmp++;
	}
	*tmp = NULL;
	closedir(dir);
	return (tmp - size);
}

t_glob	*store_match(t_mini *mini, char **tmp, t_to_expand exp,
		t_glob *head_glob)
{
	t_glob	*new;
	t_glob	*head_empty;
	int		i;

	i = 0;
	head_empty = head_glob;
	while (tmp[i] != NULL)
	{
		if (match(tmp[i], exp.str, exp.litteral) && ft_strncmp(tmp[i], ".",
				ft_strlen(tmp[i]) + 1) != 0 && ft_strncmp(tmp[i], "..",
				ft_strlen(tmp[i]) + 1) != 0 && tmp[i][0] != '.')
		{
			new = wrap_malloc(mini, sizeof(t_glob));
			if (new == NULL)
				return (head_glob);
			new->file = mini_ft_strdup(mini, tmp[i]);
			new->next = head_glob->next;
			head_glob->next = new;
		}
		i++;
	}
	head_glob = head_empty->next;
	return (head_glob);
}

t_glob	*store_hidden(t_mini *mini, char **tmp, t_to_expand exp,
		t_glob *head_glob)
{
	t_glob	*new;
	t_glob	*head_empty;
	int		i;

	i = 0;
	head_empty = head_glob;
	while (tmp[i] != NULL)
	{
		if (match(tmp[i], exp.str, exp.litteral) && ft_strncmp(tmp[i], ".",
				ft_strlen(tmp[i]) + 1) != 0 && ft_strncmp(tmp[i], "..",
				ft_strlen(tmp[i]) + 1) != 0 && tmp[i][0] == '.')
		{
			new = wrap_malloc(mini, sizeof(t_glob));
			if (new == NULL)
				return (head_glob);
			new->file = mini_ft_strdup(mini, tmp[i]);
			new->next = head_glob->next;
			head_glob->next = new;
		}
		i++;
	}
	head_glob = head_empty->next;
	return (head_glob);
}

t_glob	*glob(t_mini *mini, const char *pattern, bool *litteral)
{
	t_glob		*head_glob;
	char		**tmp;
	int			size;
	t_to_expand	exp;

	exp.str = (char *)pattern;
	exp.litteral = litteral;
	size = max_file();
	tmp = store_tmp(mini, size);
	head_glob = wrap_malloc(mini, sizeof(t_glob));
	if (head_glob == NULL)
		return (NULL);
	head_glob->file = NULL;
	head_glob->next = NULL;
	if (pattern[0] == '.')
		head_glob = store_hidden(mini, tmp, exp, head_glob);
	else
		head_glob = store_match(mini, tmp, exp, head_glob);
	return (head_glob);
}
