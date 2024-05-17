#include "./builtins.h"


void	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
