/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:48:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/22 15:49:20 by kgriset          ###   ########.fr       */
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
