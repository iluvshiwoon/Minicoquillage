#include "pipex.h"
#include <stdarg.h>

void	sx_process_next_2(t_status *mystatus)
{
	mystatus->next_process = next_process(&mystatus->next_process);
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

	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envp) == -1)
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
	mystatus->cmd->mypid = fork();
	pid = mystatus->cmd->mypid;
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close (mystatus->tube[0]);
		dup2(mystatus->tube[1], 1);
		if (fdin > 2)
			dup2(fdin, 0);
		if (fdout > 2)
			dup2(fdout, 1);
		execute_simple_command_2(mystatus);
		close(mystatus->tube[1]);
	}
	else
	{
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
		close(mystatus->tube[1]);
		exit(EXIT_SUCCESS);
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
	mystatus->cmd->mypid = fork();
	pid = mystatus->cmd->mypid;
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(mystatus->tube[1]);
		if (fdin > 2)
			dup2(fdin, 0);
		execute_simple_command_2(mystatus);
	}
	else
		waitpid(pid, &status, 0);
}

void execut(t_status *mystatus)
{
	if (pipe(mystatus->tube) == -1)
		exit(1);
	while (mystatus->current_cmd > 1)
	{
		//if built_in or bin_cmd
		execute_with_pipes_2(mystatus);
		mystatus->current_cmd = mystatus->current_cmd - 1;
		sx_process_next_2(mystatus);
	}
	last_command(mystatus);
	// ft_close(mystatus);
}


/*
########################################################################
########################################################################
########################################################################


void	execute_simple_command_2(t_status *mystatus)
{
	// pid_t	pid;
	// int		status;

	// pid = fork();
	// if (pid == 0)
	// {
		if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envp) == -1)
		{
			printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
	// }
	// else
	// 	waitpid(pid, &status, 0);
}


void	execute_with_pipes_2(t_status *mystatus)
{
	pid_t	pid;
	int		status;

	if (pipe(mystatus->tube) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(mystatus->tube[0]);
		dup2(mystatus->tube[1], 1);
		close(mystatus->tube[1]);
		execute_simple_command_2(mystatus);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		close(mystatus->tube[1]);
		dup2(mystatus->tube[0], 0);
		sx_process_next_2(mystatus);
	}

}

void	last_command(t_status *mystatus)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(mystatus->tube[1]);
		dup2(mystatus->tube[0], 0);
		execute_simple_command_2(mystatus);
	}
}


// void	execute_simple_command_2(t_status *mystatus)
// {
// 	int		status;

// 		if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envp) == -1)
// 		{
// 			printf("execve simple command failed %d (%s)\n", errno,
// 				strerror(errno));
// 			exit(EXIT_FAILURE);
// 		}
// }




// void	execute_with_pipes_2(t_status *mystatus)
// {
// 	pid_t	pid;
// 	int		status;

// 	printf("LINE : %d\n", 104);
// 	pipe(mystatus->tube);
// 	if (pid == -1)
// 		exit(1);
// 	printf("LINE : %d\n", 108);
// 	if (pid == 0)
// 	{
// 		dup2(mystatus->fdin, 0);
// 		printf("HASPIPE %d\n", mystatus->cmd->_haspipe);
// 		if (mystatus->cmd->_haspipe > 0)
// 			dup2(mystatus->fdout, 1);
// 		close(mystatus->tube[0]);
// 		close(mystatus->fdout);
// 		execute_simple_command_2(mystatus);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		printf("LINE : %d\n", 122);
// 		wait(NULL);
// 		close(mystatus->tube[1]);
// 		// dup2(mystatus->tube[0], 0);
// 		mystatus->fdin = mystatus->tube[0];
// 		sx_process_next_2(mystatus); //ce deplacer au next de mystatus
// 		printf("LINE : %d\n", 128);
// 	}
// }

*/
