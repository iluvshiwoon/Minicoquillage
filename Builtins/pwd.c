#include "./builtins.h"

int ft_pwd(void)
{
	char	cwd[1024];

	if(getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	return (1);
}

