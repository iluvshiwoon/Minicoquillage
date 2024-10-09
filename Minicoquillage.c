/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minicoquillage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:17:20 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/05 13:52:48 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minicoquillage.h"

int	main(int argc, char **argv)
{
	t_control_dll	control;
    // TODO dll for memory management + malloc wrapper

    if (MODE == INTERACTIVE)
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
    else 
	{
        if (argc == 1)
            return (EXIT_FAILURE);
		    debug(argv[1]);
		return (0);
	}
	return (0);
}
