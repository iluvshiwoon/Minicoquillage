/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:55:09 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/21 11:39:49 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	print_expr(t_double_link_node * beg, t_double_link_node * end)
{
	t_double_link_node	*node;
	t_token				*token;
	char				*type[12];

	build_type(type);
	node = beg;
	printf("\n\033[47;30m EXPR \033[0m\n");
	while (node != end)
	{
		token = node->data;
		printf("    \033[1;4;31mType\033[24m:\033[0m \033[41m%s\033[0m\n",
			type[token->type]);
		printf("        \033[1;4;32mValue\033[24m:\033[0m %s$\n", token->value);
		node = node->next;
	}
}

bool is_op(int type)
{
    if (type == OR || type == AND || type == PIPE || type == CMD_SEP)
        return (true);
    return (false);
}

t_double_link_node * get_next_op(t_control_dll * control, t_double_link_node * beg)
{
    t_token * token;
    token = beg->data;
    control->node = beg;
    while (!is_op(token->type) && control->node->next)
    {
        control->node = control->node->next;    
        token = control->node->data;
    }
    return(control->node); 
}

int compute_atom(t_control_dll * control, t_double_link_node ** beg, t_double_link_node ** end, bool skip)
{
    t_double_link_node * atom_beg;
    t_double_link_node * atom_end;
    int exit_status;

    atom_beg = *beg;
    atom_end = *end;
    exit_status = EXIT_SUCCESS;
    control->token = atom_beg->data;
    if (control->token->type == OPEN_PARENTHESIS)
    {
        atom_end = atom_beg->next;
        control->token = atom_end->data;
        while (control->token->type != CLOSE_PARENTHESIS)
        {
            atom_end = atom_end->next;
            control->token = atom_end->data;
        }
        if (skip)
            return(exit_status);
        return(compute_expr(control, atom_beg->next, atom_end->previous));
    }
    if (skip)
        return(exit_status);
    control->token = atom_end->data;
    if (is_op(control->token->type))
        atom_end = atom_end->previous;
    print_expr(atom_beg,atom_end);
    return (exit_status);
}

int compute_expr(t_control_dll * control,\
                 t_double_link_node * beg, t_double_link_node * end, t_ast * ast)
{   
    int exit_status;
    t_double_link_node atom_end;
    exit_status = EXIT_SUCCESS;
    while(beg != end->next) 
    {
        exit_status = compute_atom(control,&beg,&end,false);
        control->token = beg->data;
        if (is_op(control->token->type))   
        {
            if (control->token->type == OR)     
                compute_atom(control,beg,end,true);
        }
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
    beg = control->list->first_node;
    end = control->list->last_node;
    compute_expr(control, beg, end, ast);
}
