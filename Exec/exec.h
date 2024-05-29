#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include "../42_MyLibC/mylibc.h"

typedef struct s_format
{
	int		fd_in;
	int		fd_out;
	char	**absolute_path;
	char	*cmd_to_exec;
	int		here_doc;
}			t_format;

int	redirect(int *tube, char *operator, char *file);


char	*path_of_cmd(char **env, char *cmd);
char	**ft_cmd(char **to_exec, int i, int *j, char **tokens);

int		ft_strlen2(char **tab);
void	*ft_free_tab(char **s, size_t i);
char	**ft_env(char **env);

char	*pss_permission(char **envs_path, char *cmd);
char	*get_path(char **env);
int		pss_ok(char *path);
#endif
