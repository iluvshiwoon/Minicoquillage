#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

static void	msg_error(char *arg)
{
	printf("exit: ");
	printf("%s: ", arg);
	printf("numeric argument required\n");
}

static int	is_number(char *av)
{
	char	*input;

	input = av;
	if (input[0] == '-' || (input[0] >= '0' && input[0] <= '9'))
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

void	ft_exit(char *arg)
{
	int	exit_code;

	if (arg == NULL)
		exit(0);
	exit_code = ft_atoi(arg);
	if (is_number(arg))
	{
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
