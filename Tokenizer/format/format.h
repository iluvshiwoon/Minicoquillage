#ifndef FORMAT_H
# define FORMAT_H

# include "../../Minicoquillage.h"


typedef struct s_format_cmd
{
	t_token	*cmd_name;
	t_token	**option;
	t_token	**argument;
	t_token	**infile;
	t_token	**outfile;
}	t_format_cmd;

typedef struct s_format_cli
{
	t_format_cmd	**format_cmd;
	t_token			**link_operator;
}	t_format_cli;

t_double_link_list	**cmd_isolated(t_double_link_list **list, t_double_link_list **cmds);
void	my_cmds(t_double_link_list **list);

int				exp_size(t_double_link_list **list);
t_token			**store_infile(t_double_link_list **list, int size);
t_token			**store_outfile(t_double_link_list **list, int size);
t_token			**store_option(t_double_link_list **list, int size);
t_token			**store_argument(t_double_link_list **list, int size);

t_format_cmd	*format_array(t_double_link_list **list);



#endif
