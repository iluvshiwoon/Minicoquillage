#include "exec.h"
#include <stdio.h>

char	**content(void)
{
	//exemple chaine contenu dans la structure s_token
	char **cmds = (char **)malloc(sizeof(char *) * 11);
	cmds[0] = (char *)malloc(sizeof(char *) * 3);
	cmds[0] = "cat";
	cmds[1] = (char *)malloc(sizeof(char *) * 2);
	cmds[1] = "-e";
	cmds[2] = (char *)malloc(sizeof(char *) * 5);
	cmds[2] = "cmd.c";
	cmds[3] = (char *)malloc(sizeof(char *) * 1);
	cmds[3] = "|";
	cmds[4] = (char *)malloc(sizeof(char *) * 4);
	cmds[4] = "grep";
	cmds[5] = (char *)malloc(sizeof(char *) * 5);
	cmds[5] = "texte";
	cmds[6] = (char *)malloc(sizeof(char *) * 1);
	cmds[6] = "<";
	cmds[7] = (char *)malloc(sizeof(char *) * 6);
	cmds[7] = "infile";
	cmds[8] = (char *)malloc(sizeof(char *) * 1);
	cmds[8] = ">";
	cmds[9] = (char *)malloc(sizeof(char *) * 7);
	cmds[9] = "outfile";
	cmds[10] = NULL;
	return (cmds);

}

//to free
char	*abs_to_rel_cmd(char *token)
{
	char	**abs_cmd;
	char	*rel_cmd;
	size_t	len;

	abs_cmd = ft_split(token, '/');
	len = (size_t) ft_strlen2(abs_cmd);
	if (len >= 2)
	{
		rel_cmd = ft_strdup(abs_cmd[len - 1]);
		ft_free_tab(abs_cmd, len);
		return (rel_cmd);
	}
	else
	{
		rel_cmd = ft_strdup(abs_cmd[0]);
		ft_free_tab(abs_cmd, len);
		return (rel_cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**cmds;
	int		i, j;
	char	**env;
	char	*absolute_path;
	char	**to_exec;

	env = ft_env(envp);  //a faire en amont + erreur de copy au debut
	cmds = content();  //get token from structure s_token

	i = 0;
	j = 0;
	char *path_from_env = get_path(env);
	char **my_paths = ft_split((const char *)path_from_env, ':');

	//TODO:check if convert absolute path to cmd or only cmd to execve
	absolute_path = path_of_cmd(my_paths, cmds[0]);
	to_exec = ft_cmd(to_exec, i, &j, cmds);

	if (!to_exec)
		return (-1);

	if (execve(absolute_path, to_exec, NULL) == -1)
	{
		perror("Error: command not found\n");
		exit(127);
	}

}



