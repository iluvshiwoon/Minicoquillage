/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/09 13:58:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int tokenizer(t_control_dll * control)
{
	char			**multiline;
	char			*line;

	line = get_line();
	if (!line || !*line)
		return (free(line), EXIT_FAILURE);
	control->list = create_tokens(line);
	control->complete = 1;
	free(line);
	populate_tokens(control);
	if (check_error_tokens(control) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_list(control->list);
	dl_free_token_list(control->list);
	return (EXIT_SUCCESS);
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
		tokenizer(&control);
	return (0);
}
