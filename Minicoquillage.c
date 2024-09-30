/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/29 17:18:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int	main(int argc, char **argv)
{
	t_control_dll	control;

    if (MODE == TOKENIZER)
	{
        if (argc == 1)
            return (EXIT_FAILURE);
		debug(argv[1]);
		return (0);
	}
    else if (MODE == INTERACTIVE)
    {
        while (1)
        {
            if(tokenizer(&control) == EXIT_SUCCESS)
            {
                parser(&control);
                dl_free_token_list(control.list);
            }
        }
    }
	return (0);
}