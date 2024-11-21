/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:55:09 by kgriset           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

int compute_expr(t_mini * mini,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast_node * current_node);

bool is_op(int type)
{
    if (type == OR || type == AND || type == PIPE || type == CMD_SEP || type == EOE)
        return (true);
    return (false);
}

t_double_link_node * get_next_op(t_mini * mini, t_double_link_node * beg\
                                 ,t_double_link_node * end)
{
    int count_parenthesis;

    count_parenthesis = 0;
    mini->control.token = beg->data;
    if (mini->control.token->type == OPEN_PARENTHESIS)
        count_parenthesis++;
    while ((count_parenthesis || !is_op(mini->control.token->type)) && beg->next != end->next)
    {
        beg = beg->next;
        mini->control.token = beg->data;
        if (mini->control.token->type == OPEN_PARENTHESIS)
            count_parenthesis++;
        else if (mini->control.token->type == CLOSE_PARENTHESIS)
            count_parenthesis--;
    }
    return(beg); 
}

void count_token(t_double_link_node * beg,t_double_link_node * end, t_token_count * count)
{
    t_token * token;
    token = beg->data;
    while (!is_op(token->type) && beg && beg != end->next)
    {
        token = beg->data;
        if (token->type == COMMAND)
            count->cmd++;
        else if (token->type == ARG || token->type == OPTION)
            count->args++;
        else if (token->type == HERE_DOC)
            count->heredoc_eof++;
        else if (token->type == REDIRECTION)
        {
            if (token->value[0] == '>')
                count->std_out++;
            else
                count->std_in++;
        }
        beg = beg->next;
    }
}

void alloc_atom(t_mini * mini,t_token_count count, t_atom * atom)
{
    atom->std_in = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*atom->std_in)*(count.std_in + 1));
    atom->std_in[count.std_in] = NULL;
    atom->std_out = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*atom->std_out)*(count.std_out + 1));
    atom->std_out[count.std_out] = NULL;
    atom->append = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*atom->append)*(count.std_out));
    atom->args = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*atom->args)*(count.args + count.cmd + 1));
    atom->args[count.args + count.cmd] = NULL;
    atom->heredoc_eof = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*atom->heredoc_eof)*(count.heredoc_eof + 1));
    atom->heredoc_eof[count.heredoc_eof] = NULL;
}


void fill_in(t_atom * atom, t_double_link_node * beg, t_double_link_node * end)
{
    t_token * token;
    t_token_count count;
    
    count = (t_token_count){};
    token = beg->data;
    while (!is_op(token->type) && beg && beg != end->next)
    {
        token = beg->data;
        if (token->type == COMMAND)
        {
            atom->cmd = token->value;
            atom->args[count.args++] = token->value;
        }
        else if (token->type == ARG || token->type == OPTION)
            atom->args[count.args++] = token->value;
        else if (token->type == HERE_DOC)
            {
                atom->heredoc = true;
                token = beg->next->data;
                atom->heredoc_eof[count.heredoc_eof++] = token->value;
            }
        else if (token->type == REDIRECTION)
        {
            if (token->value[0] == '>')
            {
                if (token->value[1] == '>')
                    atom->append[count.std_out] = true;
                else 
                    atom->append[count.std_out] = false;
                token = beg->next->data;
                atom->std_out[count.std_out++] = token->value;
            }
            else
            {
                atom->heredoc = false;
                token = beg->next->data;
                atom->std_in[count.std_in++] = token->value;
            }
        }
        beg = beg->next;
    }
}

int fill_atom(t_mini * mini,t_ast_node ** current_node, t_double_link_node * beg, t_double_link_node * end)
{
    t_parser_node * p_node;
    t_token_count count;

    count = (t_token_count){};
    p_node = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*p_node));
    *p_node = (t_parser_node){};
    p_node->atom = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*p_node->atom));
    *p_node->atom = (t_atom){};
    (*current_node)->left->data = p_node;
    count_token(beg,end, &count);
    alloc_atom(mini,count, p_node->atom);
    fill_in(p_node->atom, beg, end);
    return(EXIT_SUCCESS);
}

int compute_atom(t_mini * mini, t_double_link_node * beg,\
                 t_double_link_node * end, t_ast_node ** current_node)
{
    int exit_status;

    exit_status = EXIT_SUCCESS;
    (*current_node)->left = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*(*current_node)->left));
    *(*current_node)->left = (t_ast_node){};
    (*current_node)->left->previous = *current_node;
    mini->control.token = beg->data;
    if (mini->control.token->type == OPEN_PARENTHESIS)
    {
        int count = 1;
        mini->control.node = beg;
        while (count)
        {
            mini->control.node = mini->control.node->next; 
            if (!mini->control.node)
                break;
            mini->control.token = mini->control.node->data;
            if (mini->control.token->type == OPEN_PARENTHESIS)
                count++;
            else if (mini->control.token->type == CLOSE_PARENTHESIS)
                count--;
        }
        compute_expr(mini,beg->next,mini->control.node->previous,(*current_node)->left);
        (*current_node)->right = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*(*current_node)->right));
        *(*current_node)->right = (t_ast_node){};
        (*current_node)->right->previous = (*current_node);
        return(exit_status);
    }
    fill_atom(mini,current_node,beg,end);
    mini->control.token = end->data;
    if (!is_op(mini->control.token->type))
        return(exit_status);
    (*current_node)->right = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*(*current_node)->right));
    *(*current_node)->right = (t_ast_node){};
    (*current_node)->right->previous = (*current_node);
    return(exit_status);
}

void skip_through(t_mini * mini,t_parser_node * p_node, t_double_link_node * next_op)
{
    t_token * token;
    t_token_count count;
    t_double_link_node * og_next_op;

    count = (t_token_count){};
    token = NULL;
    og_next_op = next_op;
    if (!next_op)
        return;
    while (next_op->previous)
    {
        token = next_op->previous->data;
        if (token->type == CLOSE_PARENTHESIS)
            break;
        next_op = next_op->previous;
    }
    if (token && token->type != CLOSE_PARENTHESIS)
        return;
    p_node->atom = malloc(sizeof(*p_node->atom));
    *p_node->atom = (t_atom){};
    count_token(next_op,og_next_op, &count);
    alloc_atom(mini,count, p_node->atom);
    fill_in(p_node->atom, next_op, og_next_op);
}

void skip_through_parenthesis(t_mini * mini, t_parser_node * p_node, t_double_link_node * beg, t_double_link_node * next_op)
{
    t_double_link_node * i; 
    t_token_count t_count;
    t_token * token;
    int count;

    i = beg;
    count = 0;
    t_count = (t_token_count){};
    token = i->data;
    if (token->type == OPEN_PARENTHESIS)
    {
        count++;
        while(count)
        {
            i = i->next;
            if (!i)
                break;
            token = i->data;
            if (token->type == OPEN_PARENTHESIS)
                count++;
            else if (token->type == CLOSE_PARENTHESIS)
                count--;
        }
        if (i && i->next && i->next != next_op)
        {
            p_node->atom = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*p_node->atom));
            *p_node->atom = (t_atom){};
            count_token(i->next,next_op, &t_count);
            alloc_atom(mini,t_count, p_node->atom);
            fill_in(p_node->atom, i->next, next_op);
        }
    }
}

int compute_expr(t_mini * mini,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast_node * current_node)
{   
    int exit_status;
    t_double_link_node * next_op;
    t_parser_node * p_node;

    exit_status = EXIT_SUCCESS;
    while(1) 
    {
        p_node = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*p_node));
        *p_node = (t_parser_node){};
        next_op = get_next_op(mini,beg,end);
        current_node->data = p_node;
        // skip_through(p_node,next_op);
        skip_through_parenthesis(mini,p_node,beg,next_op); 
        if (next_op == end)
        {
            p_node->ops = EOE;
            // skip_through_parenthesis(p_node,beg,next_op->next); 
            compute_atom(mini,beg,end,&current_node);
            break;
        }
        mini->control.token = next_op->data;
        p_node->ops = mini->control.token->type;
        // TODO
        // Do sth here to get redirection after parenthesis + syntax error if before parenthesis + do all here doc before execution so map them
        // Weird edge case here doc before parenthesis launched before syntax error (maybe don't implement as it's weird and dumb)
        // skip_through_parenthesis(p_node,beg,next_op); 
        exit_status = compute_atom(mini, beg ,next_op, &current_node);
        current_node = current_node->right;
        beg = next_op->next;
    }
    return(exit_status);
}

t_ast * parser(t_mini * mini)
{
    t_double_link_node * beg;
    t_double_link_node * end;
    t_ast * ast;

    ast = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*ast));
    *ast = (t_ast){};
    ast->first_node = wrap_malloc(&mini->heap_allocated,mini->heap_allocated.ast,sizeof(*ast->first_node));
    *ast->first_node = (t_ast_node){};
    beg = mini->control.list->first_node;
    end = mini->control.list->last_node;
    compute_expr(mini, beg, end, ast->first_node);
    return (ast);
}
