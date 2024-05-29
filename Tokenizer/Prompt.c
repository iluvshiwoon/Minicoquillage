/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:46:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/29 16:23:03 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

char	*build_prompt(void)
{
	char	*buffer;
	char	*prompt;
	char	*temp;

	buffer = (char [200]){};
	if (!getcwd(buffer, 200))
		return (NULL);
	prompt = last_ocur(buffer, '/');
	prompt = ft_strjoin("\033[1;34m", prompt + 1);
	if (!prompt)
		return (exit(EXIT_FAILURE), NULL);
	temp = ft_strjoin(prompt, "\033[0m");
	if (!temp)
		return (free(prompt), exit(EXIT_FAILURE), NULL);
	free(prompt);
	prompt = ft_strjoin(temp,
			(char *){" via 🐚 \033[1;34m(Minicoquillage)\n🦪 → \033[0m"});
	if (!prompt)
		return (free(temp), exit(EXIT_FAILURE), NULL);
	free(temp);
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
		return (NULL);
	return (string + last);
}
