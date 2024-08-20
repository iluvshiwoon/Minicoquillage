#ifndef BUILTINS_H
# define BUILTINS_H

# define CD_ERR "cd: no such file or directory:"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../42_MyLibC/mylibc.h"


//proof of concept not finish
//check out for each ft_

void	ft_cd(char *new_path, char **env);
int		ft_pwd(void);
char	**ft_env(char **env);
void	ft_unset(char **env, char *variable);
void	ft_export(char **env, char *variable);


void	put_env(char **env);
char	*get_var_env(char *var, char **env);
int		get_env(char **env, char *var);



#endif
