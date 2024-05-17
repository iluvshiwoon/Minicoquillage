#ifndef BUILTINS_H
# define BUILTINS_H

# define CD_ERR "cd: no such file or directory:"

# include <unistd.h>
# include <stdlib.h>
# include "../42_MyLibC/mylibc.h"

void	ft_cd(char *new_path, char **env);
int		ft_pwd(void);
char	**ft_env(char **env);
void	ft_unset(char **env, char *variable);

void	put_env(char **env);
char	*get_var_env(char *var, char **env);



#endif
