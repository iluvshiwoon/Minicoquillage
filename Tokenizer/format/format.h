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


typedef struct s_info_cmd
{
	t_format_cmd	*format;
	char			**tab;
}					t_info_cmd;

typedef struct s_pipex
{
	int				infile;
	int				outfile;
	int				here_doc;
	int				tube[2];
	char			**env;
	char			**path_cmd;
	char			**cmds;
}					t_pipex;



int				expression(t_token *token);
int				exp_size(t_double_link_list **list);
t_token			**store_infile(t_double_link_list **list, int size);
t_token			**store_outfile(t_double_link_list **list, int size);
t_token			**store_option(t_double_link_list **list, int size);
t_token			**store_argument(t_double_link_list **list, int size);

t_format_cmd	*format_array(t_double_link_list **list);
int				size_cmd(t_format_cmd *cmd);
int				total_cmd2(t_double_link_list **list_o, t_double_link_node **first);
char			**tab_cmd(t_format_cmd *cmd);
void			for_exec(t_pipex **exe, t_double_link_list **list_o);





#endif
