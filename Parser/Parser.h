/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/09/23 23:07:36 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif


typedef struct s_atom {
    char * cmd;
    char ** options;
    char ** args;
    char * heredoc;
    char ** redirection;
    bool append;
    bool expand_heredoc;
} t_atom;

typedef struct s_parser_node {
    int ops;
    t_atom atom;
} t_parser_node;

void parser(t_control_dll * control);

#endif

