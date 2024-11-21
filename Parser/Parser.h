/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/20 22:22:02 by kgriset          ###   ########.fr       */
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
    char ** heredoc_eof;
    char ** std_out;
    char ** std_in;
    bool * append;
    bool heredoc;
    int in_fd; // for heredoc before execution
    int out_fd;
    char * file_heredoc;
} t_atom;

typedef struct s_parser_node {
    int ops;
    t_atom * atom;
} t_parser_node;

typedef struct s_token_count{
    int cmd;
    int options;
    int args;
    int heredoc_eof;
    int std_out;
    int std_in;
}t_token_count;

t_ast * parser(t_mini * mini);
bool is_op(int type);

#endif
