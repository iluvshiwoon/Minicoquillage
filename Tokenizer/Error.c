/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/11 17:41:10 by kgriset          ###   ########.fr       */
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
    int cmd;
    control->node = control->list->first_node->next; 
    t_token * previous_token;
    previous_token = NULL;
    // print_list(control->list);
    cmd = 0;
    if (control->list->first_node)
    {
        control->token=control->list->first_node->data;
        if (control->token->type == AND || control->token->type == OR)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (control->token->type == PIPE)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
    }
    while(control->node)
    {
        control->token = control->node->data;
        previous_token = control->node->previous->data;
        if (previous_token->type == REDIRECTION && previous_token->type == control->token->type)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == REDIRECTION && control->token->type == HERE_DOC)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == HERE_DOC && control->token->type == HERE_DOC)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == HERE_DOC && control->token->type == REDIRECTION)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if ((previous_token->type == OR || previous_token->type == AND) && (control->token->type == AND || control->token->type == OR))
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if ((previous_token->type == OR || previous_token->type == AND) && control->token->type == PIPE)
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        else if (previous_token->type == COMMAND || control->token->type == COMMAND)
            cmd = 1;
        else if (control->token->type == PIPE && (!cmd || previous_token->type == PIPE))
            return (printf("Minicoquillage: syntax error near unexpected token `%s'\n",control->token->value),dl_free_token_list(control->list),1);
        // else if ((control->token->type == COMMAND || control->token->type == ARG) && ft_sep(control->token->value[return_fist_sep(control->token->value)]))
        //     return (printf("Minicoquillage: syntax error near unexpected token '%c'\n",control->token->value[return_fist_sep(control->token->value)]),dl_free_token_list(control->list),1);
        if (control->node->next == NULL)
            previous_token = control->node->data;
        control->node = control->node->next;
    }
    if (!previous_token)
        previous_token = control->list->first_node->data;
    if (control->complete && previous_token && (previous_token->type == REDIRECTION || previous_token->type == HERE_DOC))
        return (printf("Minicoquillage: syntax error near unexpected token `newline'\n"),dl_free_token_list(control->list),1);
    else if (!control->complete && previous_token && (previous_token->type == AND || previous_token->type == OR))
        return(dl_free_token_list(control->list),2);
    return (0);
}
