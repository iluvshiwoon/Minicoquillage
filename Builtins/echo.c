#include "../Tokenizer/Tokenizer.h"
#include "./builtins.h"


/*
############################################
############################################
############################################
*/

// int	is_option(char *msg)
// {
// 	int	i;

// 	i = 0;
// 	if (msg[i] == '-')
// 		i++;
// 	else
// 		return (0);
// 	while (msg[i] == 'n')
// 		i++;
// 	if (msg[i] == 0 && ft_strlen(msg) >= 2)
// 		return (1);
// 	return (0);
// }

// int	ft_echo(char *input, int option_n)
// {
// 	// int		option_n;
// 	int		i;
// 	char	**msg;

// 	msg = ft_split(input, ' ');
// 	i = 0;
// 	option_n = 0;
// 	while (is_option(msg[i]))
// 	{
// 		i++;
// 		option_n = 1;
// 	}
// 	while (msg[i])
// 	{
// 		printf("%s", msg[i]);
// 		if (msg[i + 1] != NULL)
// 			printf(" ");
// 		i++;
// 	}
// 	if (option_n)
// 		printf("\n");
// 	// ft_putstr_fd(input, 1);
// 	// if (!option_n)
// 	// 	printf("\n");
// 	return (0);
// }

// int	main(int ac, char **av)
// {
// 	ft_echo(av[1], 0);
// 	return (0);
// }


/*
############################################
############################################
############################################
*/


int	is_option(char *msg)
{
	int	i;

	i = 0;
	while (msg[i] == ' ')
		i++;
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

int	ft_echo(char *input, int option_n)
{
	// int		option_n;
	int		i;
	char	*msg;

	i = 0;
	msg = input;
	option_n = 0;
	while (is_option(msg))
	{
		while(*msg == ' ')
			msg++;
		while(*msg != ' ')
			msg++;
		option_n = 1;
	}
	while(*msg == ' ')
			msg++;
	ft_putstr_fd(msg, 1);
	if (!option_n)
		printf("\n");
	return (0);
}

int	main(int ac, char **av)
{
	ft_echo(av[1], 0);
	return (0);
}
