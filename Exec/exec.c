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

void	setting()
{

}




int	main(int ac, char **av, char **envp)
{
	char	**cmds;
	int		i;
	char	**env;
	char	**to_exec;
	char	*absolute_path;

	env = ft_env(envp);  //erreur de copy
	cmds = content();

	i = 0;
	char *path_from_env = get_path(env);
	char **my_paths = ft_split((const char *)path_from_env, ':');

	//check is absolute path for cmd or only cmd to execve
	absolute_path = path_of_cmd(my_paths, cmds[0]);
	printf("%s\n", absolute_path);

	to_exec = ft_cmd(to_exec, i, cmds);
	if (!to_exec)
		return (-1);
	while (to_exec[i])
	{
		printf("%d : %s\n", i, to_exec[i]);
		i++;
	}
	if (execve(absolute_path, to_exec, NULL) == -1)
	{
		perror("Error: command not found\n");
		exit(127);
	}
}



