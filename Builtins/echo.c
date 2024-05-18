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
	if (msg[i] == 0 && ft_strlen(msg) >= 2)
		return (1);
	return (0);
}

void	ft_echo(char **msg)
{
	int	option_n;
	int	i;

	i = 0;
	option_n = 0;
	if (is_option(msg[0]))
	{
		i++;
		option_n = 1;
	}
	while (msg[i])
	{
		ft_printf("%s", msg[i]);
		if (msg[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if(!option_n)
		ft_printf("\n");

}

int	main(void)
{
	char	*test[4];
	test[0] = "-n";
	test[1] = "hello";
	test[2] = "word";
	test[3] = NULL;
	int i = is_option(test[0]);

	ft_printf("%d\n", i);
	ft_echo(test);
	ft_echo(test);

	return (0);
}
