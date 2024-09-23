/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:55:09 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/23 23:10:06 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
int compute_expr(t_control_dll * control,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast_node * current_node);

bool is_op(int type)
{
    if (type == OR || type == AND || type == PIPE || type == CMD_SEP)
        return (true);
    return (false);
}

t_double_link_node * get_next_op(t_control_dll * control, t_double_link_node * beg)
{
    control->token = beg->data;
    control->node = beg;
    while (!is_op(control->token->type) && control->node->next)
    {
        control->node = control->node->next;    
        control->token = control->node->data;
    }
    return(control->node); 
}

int compute_atom(t_control_dll * control, t_double_link_node * beg,\
                 t_double_link_node * end, t_ast_node ** current_node)
{
    int exit_status;
    t_parser_node * p_node;

    exit_status = EXIT_SUCCESS;
    p_node = malloc(sizeof(*p_node));
    (*current_node)->left = malloc(sizeof(*(*current_node)->left));
    *(*current_node)->left = (t_ast_node){};
    *p_node = (t_parser_node){};
    (*current_node)->left->previous = *current_node;
    (*current_node)->left->data = p_node;
    control->token = end->data; //
    control->token = beg->data;
    if (control->token->type == OPEN_PARENTHESIS)
    {
        int count = 1;
        while (count)
        {
            control->node = control->node->next; 
            if (!control->node)
                break;
            control->token = control->node->data;
            if (control->token->type == OPEN_PARENTHESIS)
                count++;
            else if (control->token->type == CLOSE_PARENTHESIS)
                count--;
        }
        *current_node = (*current_node)->left;
        compute_expr(control,beg->next,control->node->previous,*current_node);
        return(exit_status);
    }
    // node->left = cmd...
    //
    (*current_node)->right = malloc(sizeof(*(*current_node)->right));
    *(*current_node)->right = (t_ast_node){};
    (*current_node)->right->previous = (*current_node);
    (*current_node) = (*current_node)->right;
    return(exit_status);
}

int compute_expr(t_control_dll * control,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast_node * current_node)
{   
    int exit_status;
    t_double_link_node * next_op;
    t_parser_node * p_node;

    exit_status = EXIT_SUCCESS;
    while(1) 
    {
        p_node = malloc(sizeof(*p_node));
        *p_node = (t_parser_node){};
        next_op = get_next_op(control,beg);
        current_node->data = p_node;
        if (next_op == end)
        {
            p_node->ops = EOE;
            compute_atom(control,beg,end,&current_node);
            //TODO add EOE op
            break;
        }
        control->token = next_op->data;
        p_node->ops = control->token->type;
        exit_status = compute_atom(control, beg ,next_op, &current_node);
        beg = next_op->next;
    }
    return(exit_status);
}

void parser(t_control_dll * control)
{
    t_double_link_node * beg;
    t_double_link_node * end;
    t_ast * ast;

    ast = malloc(sizeof(*ast));
    *ast = (t_ast){};
    ast->first_node = malloc(sizeof(*ast->first_node));
    *ast->first_node = (t_ast_node){};
    beg = control->list->first_node;
    end = control->list->last_node;
    compute_expr(control, beg, end, ast->first_node);
}
