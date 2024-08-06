#ifndef FORMATTING_H
# define FORMATTING_H
# include "../../Minicoquillage.h"

typedef struct s_format
{
	char	*_path;
	char	**_tab;
	int		_haspipe;
}	t_format;


typedef struct s_status
{
	t_double_link_node	*next_process;
	t_format			*cmd;
	char				**envp;
	int					fdin;
	int					fdout;
	int					tube[2];
}	t_status;


t_status	*init_status(t_double_link_node *node, t_status *status, char **env);

#endif
