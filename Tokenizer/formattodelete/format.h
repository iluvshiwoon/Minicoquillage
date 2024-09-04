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


typedef struct s_info_cmd
{
	t_format_cmd	*format;
	char			**tab;
}					t_info_cmd;

typedef struct s_pipex
{
	int				infile;
	int				outfile;
	int				tube[2];
	char			**env;
	char			**path_cmd;
	char			**cmds;
}					t_pipex;

int	last_outfile(t_token *infile);
int	last_infile(t_token *infile);

int				expression(t_token *token);
int				exp_size(t_double_link_list **list, t_double_link_node **node);
t_token			**store_infile(t_double_link_list **list, int size, t_double_link_node *node);
t_token			**store_outfile(t_double_link_list **list, int size, t_double_link_node *node);
t_token			**store_option(t_double_link_list **list, int size, t_double_link_node *node);
t_token			**store_argument(t_double_link_list **list, int size, t_double_link_node *node);
t_format_cmd	*format_array(t_double_link_list **list, t_double_link_node **node);

int				size_cmd(t_format_cmd *cmd);
int				total_cmd2(t_double_link_list **list_o, t_double_link_node **first);
char			**tab_cmd(t_format_cmd *cmd);

void	format_pipe(t_double_link_list **list, t_double_link_node **node, t_pipex *p);
t_format_cmd	*for_exec( t_double_link_list **list_o, t_double_link_node **node_o);
void	exec(char **env, t_double_link_list **list, t_double_link_node **node);




#endif
