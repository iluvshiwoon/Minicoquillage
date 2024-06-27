/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/27 15:12:12 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

t_double_link_list	*tokenizer(void)
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

void	debug(char *line)
{
	t_control_dll	control;

	control.list = create_tokens(line);
	control.complete = 1;
	populate_tokens(&control);
	if (check_error_tokens(&control) == EXIT_FAILURE)
		return ;
	print_csv(control.list);
	return (dl_free_token_list(control.list));
}

int	main(int argc, char **argv)
{
	t_control_dll	control;
	int				i;

	if (argc == 2)
	{
		debug(argv[1]);
		return (0);
	}
	while (1)
		control.list = tokenizer();
	return (0);
}
