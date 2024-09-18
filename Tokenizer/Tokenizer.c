/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/18 17:23:40 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int tokenizer(t_control_dll * control)
{
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

void print_first_token (t_control_dll * control)
{
    t_token * first_token;    
    first_token = control->list->first_node->data;

    printf("%s", first_token->value);
    return;
}

void	debug(char *line)
{
	t_control_dll	control;

	control.list = create_tokens(line);
	control.complete = 1;
	populate_tokens(&control);
	if (check_error_tokens(&control) == EXIT_FAILURE)
		return ;
    if (MODE == DEBUG)
        print_csv(control.list);
    else if (MODE == EXPANSION)
        print_first_token(&control); 
    return (dl_free_token_list(control.list));
}
