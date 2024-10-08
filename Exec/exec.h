#ifndef EXEC_H
# define EXEC_H

# include "../Tokenizer/formattoexe/formatting.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>
# include "../42_MyLibC/mylibc.h"
# include "../Builtins/builtins.h"

char	**content(void);


char	*ft_sx_path(char *cmd, t_mylist *env_var);
void	content_cmd(t_double_link_list **to_exec, t_double_link_list **list);



char	*path_of_cmd(char **env, char *cmd);
char	**ft_cmd(char **to_exec, int *i, char **tokens);

int		ft_strlen2(char **tab);
void	*ft_free_tab(char **s, size_t i);

int		pss_ok(char *path);
char	*pss_permission(char **envs_path, char *cmd);
char	*get_path(t_mylist *env);
int		pss_ok(char *path);
#endif
