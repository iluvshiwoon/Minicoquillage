/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/31 16:36:14 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
        if (control->node->next == NULL)
            previous_token = control->node->data;
        control->node = control->node->next;
    }
    if (previous_token && (previous_token->type == REDIRECTION || previous_token->type == HERE_DOC))
        return (printf("Minicoquillage: syntax error near unexpected token 'newline'\n"),dl_free_token_list(control->list),1);
    return (0);
}
