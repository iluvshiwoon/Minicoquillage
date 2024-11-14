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
int				ft_unset(t_mylist *env, char *variable);
int				ft_export(t_mylist *env, char *variable);
// void			ft_exit(int status);
void			ft_exit(char **input);
int				ft_echo(char *msg, int option_n);

//t_expand	*ft_expand(char *content, char **env);
char	*my_vpath(char *vpath, t_mylist *curpath);
void	put_envc(t_mylist *env);
char	*get_var_env(char *var, char **env);
int		get_env(char **env, char *var);
char	**env_to_tab(t_mylist *env);


size_t	ft_tab2len(char **env);
void	*ft_free_tab(char **s, size_t i);
void	*ft_free_envl(t_mylist *s);


int		mini_echo(char **args);
int		mini_pwd(char **args);
int		mini_env(char **env);
int		mini_cd(char **args, char ***env);
int		mini_export(char **args, char ***env);
int		mini_exit(char **args);
int		mini_unset(char **args, char ***env);







#endif