// #include "pipex.h"
// #include <stdarg.h>

// t_status	*sx_process_next_2(t_status *mystatus)
// {
// 	if (!mystatus->next_process)
// 		mystatus = NULL;
// 	else
// 		mystatus = init_status(mystatus->next_process, mystatus, mystatus->envp);
// 	return (mystatus);
// }

// int	open_file(char *file, int in_or_out)
// {
// 	int	fd;

// 	fd = -1;
// 	if (in_or_out == 0)
// 		fd = open(file, O_RDONLY, 0777);
// 	if (in_or_out == 1)
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (in_or_out == 2)
// 		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	return (fd);
// }

// int	handle_redirect_read(t_status *mystatus)
// {
// 	int	fdin;

// 	fdin = 0;
// 	if (mystatus->fdin != NULL)
// 	{
// 		fdin = open_file(mystatus->fdin, 0);
// 		printf("fdin file = %d\n", fdin);
// 	}
// 	return (fdin);
// }

// int	handle_redirect_write(t_status *mystatus)
// {
// 	int	fdout;

// 	fdout = 1;
// 	if (mystatus->fdout != NULL)
// 		fdout = open_file(mystatus->fdout, 1);
// 	return (fdout);
// }

// void	execute_simple_command_2(t_status *mystatus)
// {
// 	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1)
// 	{
// 		printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}
// }


// void	run_command(t_status *mystatus, int total_cmd)
// {
// 	int		status;
// 	pid_t	pid;

// 	pid = fork();

// }




// void	execut(t_status *mystatus)
// {
// 	int	j;
// 	int	*buff_tube;
// 	int	nb_cmd;

// 	j = 0;
// 	buff_tube = mystatus->cmd->tube;
// 	nb_cmd = mystatus->nb_cmd;
// 	while (mystatus)
// 	{
// 		if (pipe(mystatus->cmd->tube) == -1)
// 			exit(1);
// 		run_command(mystatus, nb_cmd, mystatus->current_cmd, buff_tube);
// 		mystatus = sx_process_next_2(mystatus);
// 		// if (*buff_tube)
// 		// 	printf("prev_tube: %d\n", *buff_tube);
// 	}
// }
