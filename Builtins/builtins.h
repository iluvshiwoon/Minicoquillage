#ifndef BUILTINS_H
# define BUILTINS_H

# define CD_ERR "cd: no such file or directory:\n"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "./../42_MyLibC/mylibc.h"

typedef struct	s_mylist
{
	void			*var;
	void			*val;
	struct s_mylist	*next;
}	t_mylist;

typedef struct	s_expand
{
	void			*content;
	struct s_expand	*next;
}	t_expand;

typedef struct	s_built
{
	char			*cmd;
	int				fdout;
}	t_built;


int	run_built(t_double_link_node *node_orig, t_mylist **env);

t_mylist		*ft_env(char **env);
int				ft_pwd(void);
int				ft_cd(char *new_path, t_mylist *env);
void			ft_unset(t_mylist *env, char *variable);
void			ft_export(t_mylist *env, char *variable);
void	ft_echo( t_double_link_node *node, t_mylist **env, int fd);
void			ft_exit(void);


t_expand	*ft_expand(char *content, char **env);

void	put_envc(t_mylist *env);
char	*get_var_env(char *var, char **env);
int		get_env(char **env, char *var);
char	**env_to_tab(t_mylist *env);

#endif
