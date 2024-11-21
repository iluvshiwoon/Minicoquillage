/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/20 23:45:44 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int tokenizer(t_mini * mini)
{
	mini->control.line = get_line(mini);
	if (!mini->control.line || !*mini->control.line)
		return (EXIT_FAILURE);
	mini->control.list = create_tokens(mini,mini->control.line);
	mini->control.complete = 1;
	populate_tokens(&mini->control);
	if (check_error_tokens(&mini->control) == EXIT_FAILURE)
		return (mini->status = 2,EXIT_FAILURE);
	// print_list(mini->control->list);
	return (EXIT_SUCCESS);
}

void print_first_token (t_control_dll * control)
{
    t_token * first_token;    
    first_token = control->list->first_node->data;

    printf("%s", first_token->value);
    return;
}

void	debug(char *line, t_mini * mini)
{
	mini->control.list = create_tokens(mini,line);
	mini->control.complete = 1;
	populate_tokens(&mini->control);
	if (check_error_tokens(&mini->control) == EXIT_FAILURE)
    {
        mini->status = 2;
		return;
    }
    execution(mini,parser(mini));
}
