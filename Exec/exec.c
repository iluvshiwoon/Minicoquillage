#include "exec.h"

void pipex()
{

}


int main(void)
{
	char *cmd_1 = "cat";
	char *cmd_2 = "cat";
	char *cmd_3 = "cat";
	char *cmd_4 = "ls -la";
	int infile = open("texte.txt", O_RDONLY);
	char *cmd[5] = {cmd_1, cmd_2, cmd_3, cmd_4, NULL};
	pid_t	id;
	int fd_pipe[2];

	id = fork();
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (id == -1)
	{
		perror("fork failed");
		exit(0);
	}
	if (!id)
		pipex(cmd, );
	else
		wait(NULL);

}
