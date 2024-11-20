/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:52 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/19 06:25:56 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	print_tree(t_heap * heap,t_ast_node * first_node)
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
            print_tree(heap,left);
            printf(") ");
        }
        else 
        {
            // if (MODE == INTERACTIVE)
            // {
            //     // char * s = get_path(heap,&status,p_node->atom->cmd);
            //     if (s)
            //         printf("%s\n",s);
            // }
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
        if(p_node->ops)
        {
            if (p_node->atom)
            {
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
            if (p_node->ops != EOE)
                printf("%s ",type[p_node->ops]);
        }
        first_node = first_node->right;
	}
}
