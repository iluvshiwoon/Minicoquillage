#include "./execution.h"

void	sx_process_next(t_status *mystatus)
{
	mystatus->next_process = next_process(&mystatus->next_process);
	mystatus = init_status(mystatus->next_process, mystatus, mystatus->envp);
}

void	execute_simple_command(t_status *mystatus)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(mystatus->cmd->_path, mystatus->cmd->_tab, mystatus->envp) == -1)
			printf("execve simple command failed %d (%s)\n", errno,
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
}

void	execute_with_pipes(t_status *mystatus)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (mystatus->next_process)
	{
		pipe(mystatus->tube);
		if ((pid = fork()) == 0)
		{
			dup2(mystatus->fdin, 0);
			if (mystatus->cmd->_haspipe > 0)
				dup2(mystatus->fdout, 1);
			close(mystatus->tube[0]);
			close(mystatus->fdout);
				// if(((t_token *)mystatus->next_process->data)->type == COMMAND)
			execute_simple_command(mystatus);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			close(mystatus->tube[1]);
			mystatus->fdin = mystatus->tube[0];
			sx_process_next(mystatus); //ce deplacer au next de mystatus
		}
	}
}
