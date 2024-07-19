#include "pipex.h"
#include <stdarg.h>

int test(char *cmd[], char **env, int input_fd, int last)
{
	pid_t	pid;
	int		tube[2];
	int		status;
	pid_t 	wpid;

	if (!last && pipe(tube) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (!last)
		{
			dup2(tube[1], STDOUT_FILENO);
			close(tube[0]);
			close(tube[1]);
		}
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		execve(ft_sx_path(cmd[0], env), cmd, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (WIFEXITED(status))
			return (0);
		if (!last)
			close(tube[1]);
		if (last)
			return (0);
		else
			return (tube[0]);
	}
}


int main(int ac, char **av, char **envp) {
	char **envcpy = ft_env(envp);
	char *cmd0[] = {"ls", NULL};
	char *cmd1[] = {"cat", NULL};
	char **cmds[] = {cmd0, cmd1, NULL};


	int input_fd = STDIN_FILENO;
	int i = 0;
	while (cmds[i + 1])
	{
		input_fd = test(cmds[i++], envcpy, input_fd, 0);
	}
	test(cmds[i], envcpy, input_fd, 1);
}

// CMD  INFILE  OUTFILE:
// cmd1 infile1 outfile1
// PIPE
// cmd2 outfile1 outfile2


