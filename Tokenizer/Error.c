/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/03 17:59:27 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
#include "stdlib.h"

size_t return_fist_sep(char * value)
{
    size_t i;
    i = 0;
    while (value[i])
    {
        if (ft_sep(value[i]))
            return i;
        ++i;
    }
    return (0);
}

int check_error_tokens(t_control_dll * control)
{
    control->node = control->list->first_node->next; 
    t_token * previous_token;

    while(control->node)
    {
        control->token = control->node->data;
        previous_token = control->node->previous->data;
        if (previous_token->type == REDIRECTION && previous_token->type == control->token->type)
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == REDIRECTION && control->token->type == HERE_DOC)
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == HERE_DOC && control->token->type == HERE_DOC)
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == HERE_DOC && control->token->type == REDIRECTION)
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if ((previous_token->type == OR || previous_token->type == AND) && (control->token->type == AND || control->token->type == OR))
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if ((previous_token->type == OR || previous_token->type == AND) && control->token->type == PIPE)
            return (printf("Minicoquillage: syntax error near unexpected token '%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if ((control->token->type == COMMAND || control->token->type == ARG) && ft_sep(control->token->value[return_fist_sep(control->token->value)]))
            return (printf("Minicoquillage: syntax error near unexpected token '%c'\n",control->token->value[return_fist_sep(control->token->value)]),dl_free_token_list(control->list),1);
        if (control->node->next == NULL)
            previous_token = control->node->data;
        control->node = control->node->next;
    }
    if (previous_token && (previous_token->type == REDIRECTION || previous_token->type == HERE_DOC))
        return (printf("Minicoquillage: syntax error near unexpected token 'newline'\n"),dl_free_token_list(control->list),1);
    return (0);
}
