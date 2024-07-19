#include "exec.h"
#include <stdio.h>
#include "../Tokenizer/Tokenizer.h"


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

char	**content(void)
{
	// exemple chaine contenu dans la structure s_token
	char **cmds = (char **)malloc(sizeof(char *) * 11);
	cmds[0] = (char *)malloc(sizeof(char *) * 4);
	cmds[0] = "cat";
	cmds[1] = (char *)malloc(sizeof(char *) * 3);
	cmds[1] = "-e";
	cmds[2] = (char *)malloc(sizeof(char *) * 3);
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
	cmds[7] = "bon";
	cmds[8] = (char *)malloc(sizeof(char *) * 1);
	cmds[8] = ">";
	cmds[9] = (char *)malloc(sizeof(char *) * 7);
	cmds[9] = "outfile";
	cmds[10] = (char *)malloc(sizeof(char *) * 1);
	cmds[10] = "<";
	cmds[11] = (char *)malloc(sizeof(char *) * 6);
	cmds[11] = "infile";
	cmds[12] = (char *)malloc(sizeof(char *) * 1);
	cmds[12] = "|";
	cmds[13] = (char *)malloc(sizeof(char *) * 2);
	cmds[13] = "ls";
	cmds[14] = NULL;
	return (cmds);
}


