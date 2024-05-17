#ifndef BUILTINS_H
# define BUILTINS_H

# define CD_ERR "cd: no such file or directory:"

# include <unistd.h>
# include <stdlib.h>
# include "../42_MyLibC/mylibc.h"

void	ft_cd(char *new_path, char **env);
int		ft_pwd(void);
char	**ft_env(char **env);
void	put_env(char **env);



#endif
