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

void ft_close(t_status *mystatus, t_status *stop)
{
	t_status *cpy_mystatus;

	cpy_mystatus = mystatus;
	while(cpy_mystatus != stop)
	{
		close(cpy_mystatus->cmd->tube[0]);
		close(cpy_mystatus->cmd->tube[1]);
		cpy_mystatus = sx_process_next_2(cpy_mystatus);
	}
	close(cpy_mystatus->cmd->tube[1]);
}

void	printExecveVars(t_status *mystatus)
{
	printf("CMD: %s\n", mystatus->cmd->_path);
	printf("CMD: %s\n", mystatus->cmd->_tab[0]);
	printf("CMD: %s\n", mystatus->cmd->_tab[1]);
}


void close_fds(int *fds)
{
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
}



void displayCmdTab(t_status *mystatus)
{
	int i = 0;
	while(mystatus->cmd->_tab[i])
	{
		ft_putstr_fd("CMD: ", 1);
		ft_putstr_fd(mystatus->cmd->_tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}


// void execute_command(t_status *mystatus, int input_fd, int output_fd)
// {
// 	int	in_fd;
// 	int	out_fd;

// 	if (mystatus->cmd->fdin_)
// 	{
// 		in_fd = handle_redirect_read(mystatus);
// 		if (in_fd < 0)
// 		{
// 			perror("open input file");
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}
// 	else if (input_fd != -1)
// 	{
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	if (mystatus->cmd->fdout_)
// 	{
// 		out_fd = handle_redirect_write(mystatus);
// 		if (out_fd < 0)
// 		{
// 			perror("open output file");
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(out_fd, STDOUT_FILENO);
// 		close(out_fd);
// 	}
// 	else if (output_fd != -1)
// 	{
// 		dup2(output_fd, STDOUT_FILENO);
// 		close(output_fd);
// 	}
// 	// displayCmdTab(mystatus);
// 	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1)
// 	{
// 		// printf("execve simple command failed %d (%s)\n", errno, strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}
// }



// void	run_command(t_status *mystatus, int total_cmd, int pos_cmd, t_status *cpy_mystatus)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	if (pid == 0)
// 	{
// 		// Si il y a une commande
// 		if (total_cmd == 1)
// 		{
// 			execute_command(mystatus, -1, -1);
// 		}
// 		// Si c' est la premiere commande, rediriger la sortie
// 		else if (pos_cmd == total_cmd)
// 		{
// 			execute_command(mystatus, -1, mystatus->cmd->tube[1]);
// 		}
// 		else if (pos_cmd != 1)
// 		{
// 			dup2(mystatus->buff[0], mystatus->cmd->tube[0]);
// 			execute_command(mystatus, mystatus->cmd->tube[0], mystatus->cmd->tube[1]);
// 		}
// 		// Si c' est la derniere commande, rediriger l'entrée
// 		else
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 			execute_command(mystatus, mystatus->buff[0], -1);
// 		}
// 	}
// 	else
// 	{
// 		if (total_cmd == 1)
// 		{
// 			waitpid(pid, &status, 0);
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 		else if (total_cmd == pos_cmd)
// 		{
// 			waitpid(pid, &status, 0);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 		else if (pos_cmd == 1)
// 		{
// 			close(mystatus->cmd->tube[0]);
// 			waitpid(pid, &status, 0);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 		else
// 		{
// 			waitpid(pid, &status, 0);
// 			dup2(mystatus->cmd->tube[0], mystatus->buff[0]);
// 			close(mystatus->cmd->tube[0]);
// 			close(mystatus->cmd->tube[1]);
// 		}
// 	}
// }



// void	execut(t_status *mystatus)
// {
// 	int			j;
// 	int			*buff_tube;
// 	int			nb_cmd;
// 	t_status	*cpy_mystatus;

// 	j = 0;
// 	mystatus->buff = mystatus->cmd->tube;
// 	nb_cmd = mystatus->nb_cmd;

// 	cpy_mystatus = mystatus;
// 	while (mystatus)
// 	{
// 		if (pipe(mystatus->cmd->tube) == -1)
// 			exit(1);
// 		run_command(mystatus, nb_cmd, mystatus->current_cmd, cpy_mystatus);
// 		mystatus = sx_process_next_2(mystatus);
// 	}
// }

void handle_error(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void execute_command(t_status *mystatus, int input_fd, int output_fd) {
	int in_fd;
	int out_fd;

	if (mystatus->cmd->fdin_) {
		in_fd = handle_redirect_read(mystatus);
		if (in_fd < 0) {
			perror("open input file");
			exit(EXIT_FAILURE);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		close(input_fd);
	} else if (input_fd != -1) {
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}

	if (mystatus->cmd->fdout_) {
		out_fd = handle_redirect_write(mystatus);
		if (out_fd < 0) {
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		close(output_fd);
	} else if (output_fd != -1) {
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}

	if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envc) == -1) {
		perror("execve");
		exit(EXIT_FAILURE);
	}
}


void run_command(t_status *mystatus, int total_cmd, int pos_cmd, int *prev_pipe) {
	pid_t pid;
	int status;
	int pipefd[2];

	if (pos_cmd < total_cmd - 1)
	{
		if (pipe(pipefd) == -1)
		{
			handle_error("pipe");
		}
	}
	pid = fork();
	if (pid == -1)
	{
		handle_error("fork");
	}
	if (pid == 0)
	{
		if (prev_pipe) {
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		if (pos_cmd < total_cmd - 1)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		execute_command(mystatus, -1, -1);
	}
	else
	{
		if (prev_pipe) {
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}

		if (pos_cmd < total_cmd - 1)
		{
			prev_pipe[0] = pipefd[0];
			prev_pipe[1] = pipefd[1];
		}
		waitpid(pid, &status, 0);
	}
}

void	execut(t_status *mystatus)
{
	int nb_cmd = mystatus->nb_cmd;
	int prev_pipe[2] = {-1, -1};
	int pos_cmd = 0;

	while (mystatus)
	{
		run_command(mystatus, nb_cmd, pos_cmd, prev_pipe);
		mystatus = sx_process_next_2(mystatus);
		pos_cmd++;
	}
}
