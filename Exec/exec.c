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
	cmds[2] = (char *)malloc(sizeof(char *) * 2);
	cmds[2] = "-n";
	cmds[3] = (char *)malloc(sizeof(char *) * 1);
	cmds[3] = "<";
	cmds[4] = (char *)malloc(sizeof(char *) * 6);
	cmds[4] = "infile";
	cmds[5] = (char *)malloc(sizeof(char *) * 1);
	cmds[5] = "|";
	cmds[6] = (char *)malloc(sizeof(char *) * 4);
	cmds[6] = "grep";
	cmds[7] = (char *)malloc(sizeof(char *) * 5);
	cmds[7] = "texte";
	cmds[8] = (char *)malloc(sizeof(char *) * 1);
	cmds[8] = "<";
	cmds[9] = (char *)malloc(sizeof(char *) * 6);
	cmds[9] = "infile";
	cmds[10] = (char *)malloc(sizeof(char *) * 1);
	cmds[10] = ">";
	cmds[11] = (char *)malloc(sizeof(char *) * 7);
	cmds[11] = "outfile";
	cmds[12] = NULL;
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

void	process(t_format format, int *i)
{
	char	*absolute_path;
	char	**to_exec;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	tube_in(format, *i);
	absolute_path = path_of_cmd(format.path, format.cmds[*i]);
	to_exec = ft_cmd(to_exec, i, format.cmds);
	if (!to_exec)
		return ;
	close(format.tube[0]);
	close(format.tube[1]);
	if (pid == 0)
	{
		if (execve(absolute_path, to_exec, NULL) == -1)
		{
			perror("Error: command not found\n");
			exit(127);
		}
	}
	else
	{
		wait(NULL);
		tube_out(format, *i);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		**env_cpy;
	int			i;
	t_format	format;
	pid_t		pid;

	format.env = ft_env(envp);  //a faire en amont + erreur de copy au debut
	format.cmds = content();  //get token from structure s_token
	format.path = ft_split((const char *)get_path(format.env), ':');
	i = 0;
	if (pipe(format.tube) == -1)
		exit(EXIT_FAILURE);
	format.fd_in = dup(STDIN_FILENO);
	format.fd_out = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
			process(format, &i);
	return (0);
}

	// if (!to_exec)
	// 	return (-1);
	// int out = dup(STDOUT_FILENO);
	// int in = dup(STDIN_FILENO);
	// int outfile = open("outfile", O_WRONLY);
	// int infile = open("infile", O_CREAT | O_RDONLY);
	// dup2(outfile, 1);
	// dup2(infile, 0);
	// close (outfile);
	// close (infile);
	// if (execve(absolute_path, to_exec, NULL) == -1)
	// {
	// 	perror("Error: command not found\n");
	// 	exit(127);
	// }
	// dup2(out, 1);
	// dup2(in, 0);
	// close(out);
	// close(in);
