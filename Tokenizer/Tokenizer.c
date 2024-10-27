/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:48:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/27 17:57:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int tokenizer(t_control_dll * control)
{
	control->line = get_line(control->heap_allocated);
	if (!control->line || !*control->line)
		return (EXIT_FAILURE);
	control->list = create_tokens(control->heap_allocated,control->line);
	control->complete = 1;
	populate_tokens(control);
	if (check_error_tokens(control) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// print_list(control->list);
	return (EXIT_SUCCESS);
}

void print_first_token (t_control_dll * control)
{
    t_token * first_token;    
    first_token = control->list->first_node->data;

    printf("%s", first_token->value);
    return;
}

void	debug(char *line, t_control_dll * control)
{
    t_heap heap;
    t_ast * ast;

    heap.heap_allocated = control->heap_allocated;
    heap.list = control->heap_allocated->exec;
	control->list = create_tokens(control->heap_allocated,line);
	control->complete = 1;
	populate_tokens(control);
	if (check_error_tokens(control) == EXIT_FAILURE)
		return ;
    if (MODE == TOKENIZER)
        print_csv(control->list);
    else if (MODE == PARSER)
    {
        ast = parser(control);
        print_tree(&heap, ast->first_node);
    }
    // else if (MODE == EXPANSION)
    //     print_first_token(&control); 
}
