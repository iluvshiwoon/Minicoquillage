#include "./../../Builtins/builtins.h"


int main(int ac , char **av, char **env)
{

	int i;
	char *str;
	t_expand *expand_list;
	
	str = ft_strdup(av[1]);
	i = 2;
	while(av[i])
	{
		str = ft_strjoin(str, av[i]);
		i++;
		if (av[i])
			str = ft_strjoin(str, " ");
	}
	expand_list = ft_expand(str, env);
	t_expand *tmp = expand_list;
	while (tmp)
	{
		printf("%s", (char *)tmp->content);
		tmp = tmp->next;
	}
	return 0;
}
