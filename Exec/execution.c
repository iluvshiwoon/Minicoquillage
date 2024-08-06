#include "./exec.h"

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
			execute_simple_command(mystatus);
			// execute_simple_command(mystatus->cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			close(mystatus->tube[1]);
			mystatus->fdin = mystatus->tube[0];
			//process_next(mystatus); ce deplacer au next de mystatus
		}
	}
}

// (.) | (.) && .
// (.) | . | . | . && .
