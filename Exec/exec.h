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
	int		here_doc;
	int		tube[2];
	char	**env;
	char	**path;
	char	**cmds;  // change to ast
}			t_format;

char	*infile_name(char **cmds, int position);
void	tube_in(t_format format, int position);
char	*outfile_name(char **cmds, int position);
void	tube_out(t_format format, int position);

char	*path_of_cmd(char **env, char *cmd);
char	**ft_cmd(char **to_exec, int *i, char **tokens);

int		ft_strlen2(char **tab);
void	*ft_free_tab(char **s, size_t i);
char	**ft_env(char **env);

char	*pss_permission(char **envs_path, char *cmd);
char	*get_path(char **env);
int		pss_ok(char *path);
#endif
