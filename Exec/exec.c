#include "exec.h"

void pipex()
{
	while()
	{

	}
}


int main(void)
{
	char *cmd_1 = "cat";
	char *cmd_2 = "cat";
	char *cmd_3 = "ls -la";
	char *cmd_4 = "grep texte";
	int infile = open("texte.txt", O_RDONLY);
	char *cmds[5] = {cmd_1, cmd_2, cmd_3, cmd_4, NULL};
	t_format init;
	pid_t	id;
	int fd[2];
	pipe(fd);

	init.cmd_path = cmds;
	init.fd_in = fd[0];
	init.fd_out = fd[1];
	id = fork();
	if (id == -1)
	{
		perror("fork failed");
		exit(0);
	}
	if (!id)
		pipex(init);
	else
		wait(NULL);
}
