#include "pipex.h"
#include <stdarg.h>

t_status	*sx_process_next_2(t_status *mystatus)
{
	if (!mystatus->next_process)
		mystatus = NULL;
	else
		mystatus = init_status(mystatus->next_process, mystatus, mystatus->envp);
	return (mystatus);
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

	fdin = STDIN_FILENO;
	if (mystatus->cmd->fdin_ != NULL)
		fdin = open_file(mystatus->cmd->fdin_, STDIN_FILENO);
	// printf("FDIN: %s pour %s\n", mystatus->cmd->fdin_, mystatus->cmd->_tab[0]);
	return (fdin);
}

int	handle_redirect_write(t_status *mystatus)
{
	int	fdout;

	fdout = STDOUT_FILENO;
	if (mystatus->cmd->fdout_ != NULL)
		fdout = open_file(mystatus->cmd->fdout_, STDOUT_FILENO);
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

void	printExecveVars(t_status *mystatus)
{
	printf("CMD: %s\n", mystatus->cmd->_path);
	printf("CMD: %s\n", mystatus->cmd->_tab[0]);
	printf("CMD: %s\n", mystatus->cmd->_tab[1]);
}

// void	m_execve(t_status *mystatus)
// {
// 	// printExecveVars(mystatus);
// 	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1)
// 	{
// 		printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}
// }

void close_fds(int *fds)
{
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
}

// void	run_command(t_status *mystatus, int total_cmd, int pos_cmd, int *buff)
// {
// 	pid_t	pid;
// 	int		status;
// 	int		fds[2];

// 	fds[0] = handle_redirect_read(mystatus);
// 	fds[1] = handle_redirect_write(mystatus);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	if (pid == 0)
// 	{
// 		// Si il y a une commande
// 		if (total_cmd == 1)
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			if (fds[0] > 2)
// 				dup2(fds[0], 0);
// 			if (fds[1] > 2)
// 				dup2(fds[1], 1);
// 		}
// 		// Si c' est la premiere commande, rediriger la sortie
// 		else if (pos_cmd == total_cmd)
// 		{
// 			{
// 				dup2(fds[0], STDIN_FILENO);
// 				close(mystatus->cmd->tube[0]);
// 				{
// 					if (dup2(mystatus->cmd->tube[1], STDOUT_FILENO) == -1)
// 						perror("T1");
// 				}
// 				// dup2(STDOUT_FILENO, fds[1]);

// 			}
// 		}
// 		else if (pos_cmd != 1)
// 		{
// 			if (fds[0] < 2 && fds[1] < 2)
// 			{
// 				dup2(buff[0], mystatus->cmd->tube[0]);
// 				dup2(mystatus->cmd->tube[0] , STDIN_FILENO);
// 				close(mystatus->cmd->tube[0]);
// 				dup2(mystatus->cmd->tube[1], STDOUT_FILENO);
// 			}
// 		}
// 		// Si c' est la derniere commande, rediriger l'entrée
// 		else
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			if (fds[0] < 2)
// 			{
// 				if (dup2(buff[0], STDIN_FILENO) == -1)
// 					perror("T6");
// 			}
// 			else
// 			{
// 				close(buff[0]);
// 				if (dup2(fds[0], STDIN_FILENO) == -1)
// 					perror("T7");
// 			}
// 			if (fds[1] > 2)
// 			{
// 				if (dup2(fds[1], STDOUT_FILENO) == -1)
// 					perror("T7");
// 			}
// 		}
// 		//close condition
// 		if (pos_cmd == total_cmd)
// 		{
// 			close_fds(fds);
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 		else if (pos_cmd != 1)
// 		{
// 			close_fds(fds);
// 			close(buff[0]);
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 		else
// 		{
// 			close_fds(fds);
// 			close(buff[0]);
// 		}
// 		m_execve(mystatus);
// 	}
// 	else
// 	{
// 		if (total_cmd == 1)
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			waitpid(pid, &status, 0);
// 			close_fds(fds);
// 		}
// 		else if (total_cmd == pos_cmd)
// 		{
// 			close(mystatus->cmd->tube[1]);
// 			waitpid(pid, &status, 0);
// 			close_fds(fds);
// 		}
// 		else if (pos_cmd == 1)
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			waitpid(pid, &status, 0);
// 			close_fds(fds);
// 		}
// 		else
// 		{
// 			dup2(mystatus->cmd->tube[0], buff[0]);
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			waitpid(pid, &status, 0);
// 			close_fds(fds);
// 		}
// 	}
// }



// void	execut(t_status *mystatus)
// {
// 	int		j;
// 	int		*buff_tube;
// 	int		nb_cmd;

// 	j = 0;
// 	buff_tube = mystatus->cmd->tube;
// 	nb_cmd = mystatus->nb_cmd;
// 	while (mystatus)
// 	{
// 		if (pipe(mystatus->cmd->tube) == -1)
// 			exit(1);
// 		run_command(mystatus, nb_cmd, mystatus->current_cmd, buff_tube);
// 		mystatus = sx_process_next_2(mystatus);
// 	}
// }





void execute_command(t_status *mystatus, int input_fd, int output_fd)
{
	int in_fd, out_fd;

	if (mystatus->cmd->fdin_)
	{
		in_fd = handle_redirect_read(mystatus);
		if (in_fd < 0)
		{
			perror("open input file");
			exit(EXIT_FAILURE);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
	}
	close(input_fd);
	if (mystatus->cmd->fdout_)
	{
		out_fd = handle_redirect_write(mystatus);
		if (out_fd < 0)
		{
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else if (output_fd != -1)
	{
		dup2(output_fd, STDOUT_FILENO);
	}
	close(output_fd);
	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1)
	{
		printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
}



void	run_command(t_status *mystatus, int total_cmd, int pos_cmd, int *buff)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		// Si il y a une commande
		if (total_cmd == 1)
		{
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			execute_command(mystatus, -1, -1);
		}
		// Si c' est la premiere commande, rediriger la sortie
		else if (pos_cmd == total_cmd)
		{
			close(mystatus->cmd->tube[0]);
			execute_command(mystatus, -1, mystatus->cmd->tube[1]);
		}
		else if (pos_cmd != 1)
		{
			{
				dup2(buff[0], mystatus->cmd->tube[0]);
				dup2(mystatus->cmd->tube[0] , STDIN_FILENO);
				dup2(mystatus->cmd->tube[1], STDOUT_FILENO);
				close(mystatus->cmd->tube[0]);
			}
			execute_command(mystatus, mystatus->cmd->tube[0], mystatus->cmd->tube[1]);
		}
		// Si c' est la derniere commande, rediriger l'entrée
		else
		{
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			execute_command(mystatus, buff[0], -1);
		}
	}
	else
	{
		if (total_cmd == 1)
		{
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			waitpid(pid, &status, 0);
		}
		else if (total_cmd == pos_cmd)
		{
			dup2(mystatus->cmd->tube[0], buff[0]);
			dup2(mystatus->cmd->tube[1], buff[1]);
			close(mystatus->cmd->tube[1]);
			waitpid(pid, &status, 0);
		}
		else if (pos_cmd == 1)
		{
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			waitpid(pid, &status, 0);
		}
		else
		{
			dup2(mystatus->cmd->tube[0], buff[0]);
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			waitpid(pid, &status, 0);
		}
	}
}

//stop

void	execut(t_status *mystatus)
{
	int		j;
	int		*buff_tube;
	int		nb_cmd;

	j = 0;
	buff_tube = mystatus->cmd->tube;
	nb_cmd = mystatus->nb_cmd;
	while (mystatus)
	{
		if (pipe(mystatus->cmd->tube) == -1)
			exit(1);
		run_command(mystatus, nb_cmd, mystatus->current_cmd, buff_tube);
		mystatus = sx_process_next_2(mystatus);
	}
}
