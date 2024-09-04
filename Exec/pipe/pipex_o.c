#include "pipex.h"
#include <stdarg.h>

void	sx_process_next_2(t_status *mystatus)
{
	mystatus = init_status(mystatus->next_process, mystatus, mystatus->envp);
}

int	open_file(char *file, int in_or_out)
{
	int	fd;

	fd = -1;
	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

int	handle_redirect_read(t_status *mystatus)
{
	int	fdin;

	fdin = 0;
	if (mystatus->fdin != NULL)
	{
		fdin = open_file(mystatus->fdin, 0);
		printf("fdin file = %d\n", fdin);
	}
	return (fdin);
}

int	handle_redirect_write(t_status *mystatus)
{
	int	fdout;

	fdout = 1;
	if (mystatus->fdout != NULL)
		fdout = open_file(mystatus->fdout, 1);
	return (fdout);
}

void ft_close(t_status *mystatus, int in , int out)
{
	close(mystatus->tube[0]);
	close(mystatus->tube[1]);
	if (in > STDERR_FILENO)
		close(in);
	if (out > STDERR_FILENO)
		close(out);
}

void	execute_simple_command_2(t_status *mystatus)
{
	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1)
	{
		printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}


void	execute_first_pipes_2(t_status *mystatus)
{
	pid_t	pid;
	int		status;
	int		fdin;
	int		fdout;

	fdin = handle_redirect_read(mystatus);
	fdout = handle_redirect_write(mystatus);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(mystatus->tube[0]);
		if (fdout > 2)
			dup2(fdout, 1);
		else
			dup2(mystatus->tube[1], 1);
		if (fdin > 2)
			dup2(fdin, 0);
		ft_close(mystatus, fdin, fdout);
		execute_simple_command_2(mystatus);
	}
	else
	{
		close(mystatus->tube[1]);
		waitpid(pid, &status, 0);
	}
}

void	execute_with_pipes_2(t_status *mystatus)
{
	pid_t	pid;
	int		status;
	int		fdin;
	int		fdout;

	fdin = handle_redirect_read(mystatus);
	fdout = handle_redirect_write(mystatus);
	mystatus->cmd->mypid = fork();
	pid = mystatus->cmd->mypid;
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(mystatus->tube[0]);
		if (fdin > 1)
			dup2(fdin, 1);
		else
			dup2(mystatus->tube[1], 1);
		ft_close(mystatus, fdin, fdout);
		execute_simple_command_2(mystatus);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	last_command(t_status *mystatus)
{
	pid_t	pid;
	int		status;
	int		fdin;
	int		fdout;

	fdin = handle_redirect_read(mystatus);
	fdout = handle_redirect_write(mystatus);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		// close(0);
		// dup(mystatus->tube[0]);
		close(mystatus->tube[1]);
		if (fdout > 2)
			dup2(fdout, 1);
		else
			dup2(mystatus->tube[0], 0);
		if (fdin > 2)
			dup2(fdin, 0);
		ft_close(mystatus, fdin, fdout);
		execute_simple_command_2(mystatus);
	}
	else
	{
		// close(mystatus->tube[1]);
		waitpid(pid, &status, 0);
	}
}



// void execut(t_status *mystatus)
// {
// 	int nb;

// 	nb = mystatus->nb_cmd;
// 		printf("CURRENT :%d\n", mystatus->nb_cmd);
// 	if (pipe(mystatus->tube) == -1)
// 		exit(1);
// 	while (mystatus->current_cmd > 0)
// 	{
// 		if (mystatus->nb_cmd == 1)
// 			last_command(mystatus);
// 		else if (mystatus->current_cmd == nb)
// 		{
// 			printf("line 178\n");
// 			execute_first_pipes_2(mystatus);
// 		}
// 		else if (mystatus->current_cmd != 1)
// 		{
// 			printf("line 183\n");
// 			execute_first_pipes_2(mystatus);
// 			// execute_with_pipes_2(mystatus);
// 		}
// 		else
// 			last_command(mystatus);
// 		close(mystatus->tube[1]);
// 		mystatus->current_cmd = mystatus->current_cmd - 1;
// 		sx_process_next_2(mystatus);
// 		printf("Commande a exec: %s\n", mystatus->cmd->_tab[0]);
// 	}
// }



void	execut(t_status *mystatus)
{
	int		status;
	pid_t	pid;

	if (mystatus->current_cmd == 1)
		last_command(mystatus);
	else
		while (mystatus->current_cmd > 1)
		{
			if (pipe(mystatus->tube) == -1)
				exit(1);
			pid = fork();
			if (pid == -1)
				exit(1);
			if (pid == 0)
					execute_first_pipes_2(mystatus);
			else
			{
				close(mystatus->tube[1]);
				waitpid(pid, &status, 0);
			}
			mystatus->current_cmd = mystatus->current_cmd - 1;
			sx_process_next_2(mystatus);
			if (mystatus->current_cmd == 1)
				last_command(mystatus);
		}
}
