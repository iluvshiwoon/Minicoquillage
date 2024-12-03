/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 16:44:58 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

char	*get_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = build_prompt(mini);
	return (prompt);
}

char	*r_prompt(t_mini *mini, char *temp)
{
	char				*r_value;
	char				*shell;

	shell = _getenv(mini, "SHELL");
	if (!shell)
		shell = ".";
	if (mini->status)
	{
		r_value = mini_ft_strjoin(mini, temp,
				mini_ft_strjoin(mini, mini_ft_strjoin(mini,
						" via \1\033[1;34m\2", last_ocur(shell, '/') + 1),
					"\1\n🦪\2 \1\033[31m→\2 \1\033[0m\2"));
	}
	else
	{
		r_value = mini_ft_strjoin(mini, temp, mini_ft_strjoin(mini,
					mini_ft_strjoin(mini,
						" via \1\033[1;34m\2", last_ocur(shell, '/') + 1),
					"\1\n🦪\2 \1\033[32m→\2 \1\033[0m\2"));
	}
	return (r_value);
}

char	*build_prompt(t_mini *mini)
{
	char	*buf;
	char	*prompt;
	char	*temp;
	bool	to_free;

	to_free = false;
	buf = _getenv(mini, "PWD");
	if (!buf)
	{
		buf = getcwd(NULL, 0);
		to_free = true;
	}
	temp = buf;
	if (!buf)
		buf = mini_ft_strdup(mini, ".");
	buf = mini_ft_strdup(mini, buf);
	if (to_free == true)
		free(temp);
	prompt = last_ocur(buf, '/');
	prompt = mini_ft_strjoin(mini, "\1\033[1;34m\2", prompt + 1);
	temp = mini_ft_strjoin(mini, prompt, "\1\033[0m\2");
	prompt = r_prompt(mini, temp);
	return (prompt);
}

char	*last_ocur(char *string, char c)
{
	size_t	i;
	size_t	last;

	i = 0;
	last = 0;
	while (string[i])
	{
		if (string[i] == c)
			last = i;
		i++;
	}
	if (!last)
		return (string - 1);
	return (string + last);
}
