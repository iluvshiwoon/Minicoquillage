#include "./builtins.h"

int ft_pwd(void)
{
	// char	cwd[1024];
	char *cwd;

	cwd = getcwd(NULL, 0);
	// if (getcwd(cwd, sizeof(cwd)))
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	return (1);
}


