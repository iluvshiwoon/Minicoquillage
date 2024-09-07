#ifndef FORMATTING_H
# define FORMATTING_H
# include "../../Minicoquillage.h"

typedef struct s_format
{
	char	*_path;
	char	**_tab;
	int		_haspipe;
	int		mypid;
	int		tube[2];
}	t_format;


typedef struct s_status
{
	t_format			*cmd;
	t_mylist			*envp;
	char				**envc;
	t_double_link_node	*next_process;
	char				*fdin;
	char				*fdout;
	int					nb_cmd;
	int					current_cmd;
	int					tube[];
}	t_status;

t_double_link_node	*next_process(t_double_link_node **node);
t_status			*init_status(t_double_link_node *node, t_status *status, t_mylist *env);

#endif
