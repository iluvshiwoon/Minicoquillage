#include "../Minicoquillage.h"

static void	msg_error(char *arg)
{
    size_t w_bytes;

    w_bytes = 0;
	w_bytes = write(2, "exit: ", 6);
	w_bytes = write(2, arg, ft_strlen(arg));
	w_bytes = write(2, ": numeric argument required\n",28);
    if (w_bytes)
        return;
}

static void msg_error_too_many_args(void)
{
    size_t w_bytes;
	w_bytes = write(2, "exit: too many arguments\n", 25);
    if (w_bytes)
        return;
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

int	mini_exit(char **args)
{
	char	**input;

	input = ++args;
	ft_exit(input);
	return (0);
}
