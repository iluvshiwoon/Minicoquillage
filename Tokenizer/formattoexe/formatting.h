#ifndef FORMATTING_H
# define FORMATTING_H
# include "../../Minicoquillage.h"

typedef struct s_format
{
	char	*_path;
	char	**_tab;
	int		_haspipe;
	int		mypid;
}	t_format;


typedef struct s_status
{
	t_format			*cmd;
	char				**envp;
	t_double_link_node	*next_process;
	char				*fdin;
	char				*fdout;
	int					tube[2];
	int					nb_cmd;
	int					current_cmd;
}	t_status;

t_double_link_node	*next_process(t_double_link_node **node);
t_status			*init_status(t_double_link_node *node, t_status *status, char **env);

#endif
