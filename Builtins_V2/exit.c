#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

static void	msg_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n",2);
}

static void msg_error_too_many_args(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
}

static int	is_number(char *av)
{
	char	*input;

	input = av;
	if ((input[0] == '-' || input[0] == '+') || (input[0] >= '0' && input[0] <= '9'))
		input++;
	else
		return (0);
	while (*input)
	{
		if (*input < '0' || *input > '9')
			return (0);
		input++;
	}
	return (1);
}

void	ft_exit(char **input)
{
	int	exit_code;
	char	*arg;

	arg = input[0];
	if (arg == NULL)
		exit(0);
	exit_code = ft_atoi(arg);
	if (is_number(arg))
	{
		if (input[1] != NULL)
		{
			msg_error_too_many_args();
			exit(1);
		}
		if (exit_code < 0)
			exit(256 - ((-1 * exit_code) % 256));
		else
			exit(exit_code % 256);
	}
	else
	{
		msg_error(arg);
		exit(2);
	}
}

void mini_exit(char **args)
{
	char	**input;

	input = ++args;
	ft_exit(input);
}