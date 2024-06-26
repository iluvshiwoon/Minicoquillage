/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 15:15:51 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

t_double_link_list	**tokenizer(void)
{
	char			**multiline;
	char			*line;
	t_control_dll	control;

	line = get_line();
	if (!line || !*line)
		return (free(line), NULL);
	control.list = create_tokens(line);
	control.complete = 1;
	free(line);
	populate_tokens(&control);
	if (check_error_tokens(&control) == EXIT_FAILURE)
		return (NULL);
	print_list(control.list);
	dl_free_token_list(control.list);
	return (NULL);
}

t_double_link_list	**debug(char *line)
{
	t_control_dll	control;

	control.list = create_tokens(line);
	control.complete = 1;
	populate_tokens(&control);
	if (check_error_tokens(&control) == EXIT_FAILURE)
		return (NULL);
	print_csv(control.list);
	return (dl_free_token_list(control.list), NULL);
}

int	main(int argc, char **argv)
{
	t_double_link_list	**tokens_lists;
	int					i;

	if (argc == 2)
	{
		tokens_lists = debug(argv[1]);
		return (0);
	}
	while (1)
		tokens_lists = tokenizer();
	return (0);
}
