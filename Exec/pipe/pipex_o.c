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
	if (pipe(mystatus->tube) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
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
		close(mystatus->tube[1]);
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
	if (pipe(mystatus->tube) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
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
		close(mystatus->tube[1]);
		waitpid(pid, &status, 0);
	}
}

void	init_pipefds(t_status *mystatus, int tube[])
{
	int	i;
	int	nb;

	tube = malloc(sizeof(int) * ((mystatus->nb_cmd - 1) * 2));
	nb = mystatus->nb_cmd - 1;
	if (nb != 0)
	{
		i = 0;
		while (i < (2 * (nb)))
		{
			if (pipe(&tube[i]) == -1)
				exit(1);
			i++;
		}
	}
}


int	close_pipefds(t_status *mystatus)
{
	int	i;
	int	nb;

	nb = mystatus->nb_cmd - 1;
	if (nb != 0)
	{
		i = 0;
		while (i < (2 * (nb - 1)))
		{
			close(mystatus->tube[i]);
			i++;
		}
		return (0);
	}
	return (1);
}


// void	run_command(t_status *mystatus, int j, int tube[])
// {
// 	pid_t	pid;
// 	int		status;
// 	int		fdin;
// 	int		fdout;

// 	fdin = handle_redirect_read(mystatus);
// 	fdout = handle_redirect_write(mystatus);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	if (pid == 0)
// 	{
// 		// Si ce n'est pas la première commande, rediriger l'entrée
// 		if (j != 0)
// 		{
// 			if (dup2(tube[(j - 1) * 2], STDIN_FILENO) < 0)
// 			{
// 				perror("dup2");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		// Si ce n'est pas la dernière commande, rediriger la sortie
// 		if (j != mystatus->nb_cmd - 1)
// 		{
// 			if (dup2(tube[j * 2 + 1], STDOUT_FILENO) < 0)
// 			{
// 				perror("dup2");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		close_pipefds(mystatus);
// 		execute_simple_command_2(mystatus);
// 	}
// 	else
// 	{
// 		close_pipefds(mystatus);
// 		waitpid(pid, &status, 0);
// 	}
// }

void	run_command(t_status *mystatus, int total_cmd, int pos_cmd, int *buff)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		// Si c' est la premiere commande, rediriger la sortie
		if (pos_cmd == total_cmd)
		{
			close(mystatus->cmd->tube[0]);
			if (dup2(mystatus->cmd->tube[1], STDOUT_FILENO) < 0)
			{
				perror("dup2-f");
				exit(EXIT_FAILURE);
			}
		}
		else if (pos_cmd != 1)
		{
			dup2(buff[0], mystatus->cmd->tube[0]);
			dup2(mystatus->cmd->tube[0] , STDIN_FILENO);
			close(mystatus->cmd->tube[0]);
			if (buff[0]> 3)
				ft_putnbr_fd(buff[0], 2);
			if (dup2(mystatus->cmd->tube[1], STDOUT_FILENO) == -1)
				perror("dup2-tube2");
		}
		// Si c' est la derniere commande, rediriger l'entrée
		else
		{
			close(mystatus->cmd->tube[0]);
			close(mystatus->cmd->tube[1]);
			if (dup2(buff[0], STDIN_FILENO) < 0)
			{
				perror("dernier-dup2-l");
				printf("dernier-cmd-dup2 %d (%s)\n", errno, strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		//close condition
		if (pos_cmd == total_cmd)
		{
			close(mystatus->cmd->tube[1]);
		}
		else if(pos_cmd == 1)
		{
			if(close(buff[0]) == -1)
				perror("dernier-buff-close");
		}
		else
		{
			if(close(buff[0]) == -1)
				perror("buff-close");
			if(close(mystatus->cmd->tube[1]) == -1)
				perror("midcmd-tube1-close");
		}
		execute_simple_command_2(mystatus);
	}
	else
	{
		if (total_cmd == pos_cmd)
		{
			close(mystatus->cmd->tube[1]);
			buff = &mystatus->cmd->tube[0];
			waitpid(pid, &status, 0);
		}
		else if (pos_cmd == 1)
		{
			close(mystatus->cmd->tube[1]);
			close(mystatus->cmd->tube[0]);
			// close(buff[0]);
			waitpid(pid, &status, 0);
		}
		else
		{
			close(mystatus->cmd->tube[1]);
			dup2(mystatus->cmd->tube[0], buff[0]);
			close(mystatus->cmd->tube[0]);
			waitpid(pid, &status, 0);
		}
	}
}

// Version 0
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
// 			execute_first_pipes_2(mystatus);
// 		else if (mystatus->current_cmd != 1)
// 		{
// 			execute_first_pipes_2(mystatus);
// 			// execute_with_pipes_2(mystatus);
// 		}
// 		else
// 			last_command(mystatus);
// 		close(mystatus->tube[1]);
// 		mystatus->current_cmd = mystatus->current_cmd - 1;
// 		sx_process_next_2(mystatus);
// 	}
// }


// Version 1
// void	execut(t_status *mystatus)
// {
// 	int		status;
// 	pid_t	pid;

// 	if (mystatus->current_cmd == 1)
// 		last_command(mystatus);
// 	else
// 		while (mystatus->current_cmd > 1)
// 		{
// 			if (pipe(mystatus->tube) == -1)
// 				exit(1);
// 			pid = fork();
// 			if (pid == -1)
// 				exit(1);
// 			if (pid == 0)
// 				execute_first_pipes_2(mystatus);
// 			else
// 			{
// 				close(mystatus->tube[1]);
// 				waitpid(pid, &status, 0);
// 			}
// 			mystatus->current_cmd = mystatus->current_cmd - 1;
// 			sx_process_next_2(mystatus);
// 			if (mystatus->current_cmd == 1)
// 				last_command(mystatus);
// 		}
// }



//version 2 GPT??
void	execut(t_status *mystatus)
{
	int	j;
	int	*buff_tube;
	int	nb_cmd;

	j = 0;
	buff_tube = mystatus->cmd->tube;
	nb_cmd = mystatus->nb_cmd;
	while (mystatus)
	{
		if (pipe(mystatus->cmd->tube) == -1)
			exit(1);
		run_command(mystatus, nb_cmd, mystatus->current_cmd, buff_tube);
		mystatus = sx_process_next_2(mystatus);
		// if (*buff_tube)
		// 	printf("prev_tube: %d\n", *buff_tube);
	}
}
