/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:13:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int	tokenizer(t_mini *mini)
{
	mini->list = mini->heap_allocated.input;
	mini->control.line = get_line(mini);
	if (!mini->control.line || !*mini->control.line)
		return (close_fds(mini->fds), EXIT_FAILURE);
	mini->list = mini->heap_allocated.tokens;
	mini->control.list = create_tokens(mini, mini->control.line);
	mini->control.complete = 1;
	populate_tokens(&mini->control);
	if (check_error_tokens(&mini->control) == EXIT_FAILURE)
		return (close_fds(mini->fds), mini->status = 2, EXIT_FAILURE);
	return (close_fds(mini->fds), EXIT_SUCCESS);
}

void	debug(char *line, t_mini *mini)
{
	mini->control.list = create_tokens(mini, line);
	mini->control.complete = 1;
	populate_tokens(&mini->control);
	if (check_error_tokens(&mini->control) == EXIT_FAILURE)
	{
		mini->status = 2;
		return ;
	}
	execution(mini, parser(mini));
}
