#ifndef BUILTINS_H
# define BUILTINS_H

# define CD_ERR "cd: no such file or directory:"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../42_MyLibC/mylibc.h"

typedef struct s_mylist
{
	void		*var;
	void		*val;
	struct s_mylist	*next;
}	t_mylist;


//proof of concept not finish
//check out for each ft_

t_mylist	*ft_env(char **env);
int			ft_pwd(void);
void		ft_unset(t_mylist *env, char *variable);
void	ft_cd(char *new_path, char **env);
void	ft_export(char **env, char *variable);


void	put_env(t_mylist *env);
char	*get_var_env(char *var, char **env);
int		get_env(char **env, char *var);

#endif
