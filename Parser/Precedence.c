/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:55:09 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/25 21:05:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
bool is_op(int type);

int compute_expr(t_control_dll * control,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast_node * current_node);

void print_t_options(t_atom * atom)
{
    int i;
    i = -1;
    while(atom->options[++i])
        printf("%s ",atom->options[i]);
}

void print_t_args(t_atom * atom)
{
    int i;
    i = -1;
    while(atom->args[++i])
        printf("%s ",atom->args[i]);
}

void print_t_heredoc(t_atom * atom)
{
    int i;
    i = -1;
    while(atom->heredoc_eof[++i])
        printf("<< %s ",atom->heredoc_eof[i]);
}

void print_t_stdin(t_atom * atom)
{
    int i;
    i = -1;
    while(atom->std_in[++i])
        printf("< %s ",atom->std_in[i]);
}

void print_t_stdout(t_atom * atom)
{
    int i;
    i = -1;
    while(atom->std_out[++i])
    {
        if (atom->append[i])
            printf(">> %s ",atom->std_out[i]);
        else
            printf("> %s ",atom->std_out[i]);
    }
}

void	build_tree_type(char **type)
{
	type[COMMAND] = "COMMAND";
	type[ARG] = "ARGUMENT";
	type[PIPE] = "|";
	type[REDIRECTION] = "REDIRECTION";
	type[HERE_DOC] = "HERE DOC";
	type[OPTION] = "OPTION";
	type[AND] = "&&";
	type[OR] = "||";
	type[OPEN_PARENTHESIS] = "OPEN PARENTHESIS";
	type[CLOSE_PARENTHESIS] = "CLOSE PARENTHESIS";
	type[CMD_SEP] = ";";
	type[R_FILE] = "FILE";
    type[EOE] = "";
}

void	print_tree(t_ast_node * first_node)
{
    t_ast_node * left;
    t_parser_node * p_node;
	char				*type[13];

	build_tree_type(type);
	while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = left->data;
        if (is_op(p_node->ops))
        {
            printf("(");
            print_tree(left);
            printf(") ");
        }
        else 
        {
            printf("%s ",p_node->atom->cmd);
            print_t_options(p_node->atom);
            print_t_args(p_node->atom);
            if (p_node->atom->heredoc)
            {
                print_t_stdin(p_node->atom);
                print_t_heredoc(p_node->atom);
            }
            else 
            {
                print_t_heredoc(p_node->atom);
                print_t_stdin(p_node->atom);
            }
            print_t_stdout(p_node->atom);
        }
        p_node = first_node->data;
        if(p_node->ops != EOE)
            printf("%s ",type[p_node->ops]);
        first_node = first_node->right;
	}
}

bool is_op(int type)
{
    if (type == OR || type == AND || type == PIPE || type == CMD_SEP || type == EOE)
        return (true);
    return (false);
}

t_double_link_node * get_next_op(t_control_dll * control, t_double_link_node * beg\
                                 ,t_double_link_node * end)
{
    int count_parenthesis;

    count_parenthesis = 0;
    control->token = beg->data;
    if (control->token->type == OPEN_PARENTHESIS)
        count_parenthesis++;
    while ((count_parenthesis || !is_op(control->token->type)) && beg->next != end->next)
    {
        beg = beg->next;
        control->token = beg->data;
        if (control->token->type == OPEN_PARENTHESIS)
            count_parenthesis++;
        else if (control->token->type == CLOSE_PARENTHESIS)
            count_parenthesis--;
    }
    return(beg); 
}

void count_token(t_double_link_node * beg, t_token_count * count)
{
    t_token * token;
    token = beg->data;
    while (!is_op(token->type) && beg)
    {
        token = beg->data;
        if (token->type == COMMAND)
            count->cmd++;
        else if (token->type == OPTION)
            count->options++;
        else if (token->type == ARG)
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

void alloc_atom(t_token_count count, t_atom * atom)
{
    atom->std_in = malloc(sizeof(*atom->std_in)*(count.std_in + 1));
    atom->std_in[count.std_in] = NULL;
    atom->std_out = malloc(sizeof(*atom->std_out)*(count.std_out + 1));
    atom->std_out[count.std_out] = NULL;
    atom->append = malloc(sizeof(*atom->append)*(count.std_out));
    atom->args = malloc(sizeof(*atom->args)*(count.args + 1));
    atom->args[count.args] = NULL;
    atom->options = malloc(sizeof(*atom->options)*(count.options + 1));
    atom->options[count.options] = NULL;
    atom->heredoc_eof = malloc(sizeof(*atom->heredoc_eof)*(count.heredoc_eof + 1));
    atom->heredoc_eof[count.heredoc_eof] = NULL;
}


void fill_in(t_atom * atom, t_double_link_node * beg)
{
    t_token * token;
    t_token_count count;
    
    count = (t_token_count){};
    token = beg->data;
    while (!is_op(token->type) && beg)
    {
        token = beg->data;
        if (token->type == COMMAND)
            atom->cmd = token->value;
        else if (token->type == OPTION)
            atom->options[count.options++] = token->value;
        else if (token->type == ARG)
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

int fill_atom(t_ast_node ** current_node, t_double_link_node * beg)
{
    t_parser_node * p_node;
    t_token_count count;

    count = (t_token_count){};
    p_node = malloc(sizeof(*p_node));
    *p_node = (t_parser_node){};
    p_node->atom = malloc(sizeof(*p_node->atom));
    *p_node->atom = (t_atom){};
    (*current_node)->left->data = p_node;
    count_token(beg, &count);
    alloc_atom(count, p_node->atom);
    fill_in(p_node->atom, beg);
    return(EXIT_SUCCESS);
}

int compute_atom(t_control_dll * control, t_double_link_node * beg,\
                 t_double_link_node * end, t_ast_node ** current_node)
{
    int exit_status;

    exit_status = EXIT_SUCCESS;
    (*current_node)->left = malloc(sizeof(*(*current_node)->left));
    *(*current_node)->left = (t_ast_node){};
    (*current_node)->left->previous = *current_node;
    control->token = beg->data;
    if (control->token->type == OPEN_PARENTHESIS)
    {
        int count = 1;
        control->node = beg;
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
        // *current_node = (*current_node)->left;
        compute_expr(control,beg->next,control->node->previous,(*current_node)->left);
        (*current_node)->right = malloc(sizeof(*(*current_node)->right));
        *(*current_node)->right = (t_ast_node){};
        (*current_node)->right->previous = (*current_node);
        return(exit_status);
    }
    // node->left = cmd...
    fill_atom(current_node,beg);
    control->token = end->data;
    if (!is_op(control->token->type))// source of leak ??
        return(exit_status);
    //
    (*current_node)->right = malloc(sizeof(*(*current_node)->right));
    *(*current_node)->right = (t_ast_node){};
    (*current_node)->right->previous = (*current_node);
    // (*current_node) = (*current_node)->right;
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
        next_op = get_next_op(control,beg,end); // fix op outside parenth
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
        current_node = current_node->right;
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
    print_tree(ast->first_node);
    printf("\n");
}
