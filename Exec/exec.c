/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/21 18:51:55 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"
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
            if (MODE == INTERACTIVE)
            {
                char * s = get_path(heap,p_node->atom->cmd);
                if (s)
                    printf("%s\n",s);
            }
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
void execution(t_heap_allocated * heap_allocated, t_ast * ast)
{
    t_heap heap;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->exec;
    print_tree(&heap,ast->first_node);
    printf("\n");
}
