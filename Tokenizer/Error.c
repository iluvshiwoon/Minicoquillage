/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:54:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/18 15:38:27 by kgriset          ###   ########.fr       */
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

void print_error(char * error, t_control_dll * control, t_token * token)
{
    if (token)
        printf(error,token->value);
    else if (!token) 
        printf(error,NULL);
    dl_free_token_list(control->list);
}

int check_error(t_control_dll * control, t_token * next)
{
    char * error = "Minicoquillage: syntax error near unexpected token `%s'\n";
    char * newline = "Minicoquillage: syntax error near unexpected token `newline'\n";
    if (!next || !control->token)
    {
        if (!next && control->token->type >= PIPE && control->token->type <= OR)
            return (CONTINUE);
        else if (!next && control->token->type >= REDIRECTION && control->token->type <= HERE_DOC)
            return (print_error(newline, control, NULL), EXIT_FAILURE);
        else if(!control->token && next->type >= CMD_SEP && next->type <= OR)
            return (print_error(error, control, next),EXIT_FAILURE);
        return(EXIT_SUCCESS);
    }
    if (control->token->type >= COMMAND && control->token->type <= HERE_DOC && next->type == control->token->type)
        return (print_error(error, control, next),EXIT_FAILURE);
    else if (control->token->type >= REDIRECTION && control->token->type <= HERE_DOC && next->type >= REDIRECTION && next->type <= HERE_DOC)
        return (print_error(error, control, next),EXIT_FAILURE);
    else if (control->token->type == REDIRECTION && next->type != ARG)
        return (print_error(error, control, next),EXIT_FAILURE);
    else if (control->token->type >= CMD_SEP && control->token->type <= OR && next->type >= CMD_SEP && next->type <= OR)
        return (print_error(error, control, next),EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int check_error_tokens(t_control_dll * control)
{
    t_token * next;
    int r_value;
    control->node = control->list->first_node;
    control->token = NULL;
    if (check_error(control, control->list->first_node->data) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    while (control->node)
    {
        control->token = control->node->data;
        if (control->node->next)
            next = control->node->next->data;
        else 
            next = NULL;
        r_value = check_error(control, next);
        if (r_value == EXIT_FAILURE)
            return (EXIT_FAILURE);
        else if (r_value == CONTINUE)
            return(CONTINUE);
        control->node=control->node->next;
    }
    if (check_error(control, next) == CONTINUE)
        return (CONTINUE);
    return (EXIT_SUCCESS);
}
