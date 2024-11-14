#include "../Tokenizer/Tokenizer.h"
#include "./builtins.h"

int	is_option(char *msg)
{
	int	i;

	i = 0;
	if (msg[i] == '-')
		i++;
	else
		return (0);
	while (msg[i] == 'n')
		i++;
	if (msg[i] == ' ' && i >= 2)
		return (1);
	return (0);
}

int mini_echo(char **args)
{
	int	opt;

	++args;
	opt = is_option(*args);
	if (opt)
		++args;
	while (args)
	{
		ft_putstr_fd(*args, 1); // write fail ?
		if (args[1])
			write(1, " ", 1); // write fail?
	}
	if (!opt)
		write(1, "\n", 1);
    return (0);
}
