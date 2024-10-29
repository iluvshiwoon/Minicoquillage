#include "./../../Builtins/builtins.h"

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

int	main(int argc, char *argv[], char *env[])
{
	int	exit_code;

	if (argv[1] == NULL)
		exit_code = 0;
	else
	{
		if (!is_number(argv[1]))
			exit_code = 2;
		else
		{
			if (ft_atoi(argv[1]) < 0)
				exit_code = (256 - ((-1 * ft_atoi(argv[1])) % 256));
			else
				exit_code = (ft_atoi(argv[1]) % 256);
		}

		if (argc > 1)
			ft_exit(++argv);
		else
			ft_exit(NULL);
	}
	return (exit_code);
}
