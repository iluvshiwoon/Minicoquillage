#include "../Tokenizer/Tokenizer.h"
#include "./builtins.h"

int	is_option(t_double_link_node *node)
{
	if (((t_token *)node->data)->type == REDIRECTION)
		return (1);
	return (0);
}

void	display_env(int fd, t_mylist **env, char *content)
{
	t_mylist	*c_env;
	int			end_;
	char		*var;

	c_env = *env;
	end_ = 0;
	while (content[end_] != ' ' || content[end_] != 0 || content[end_] != '\n')
		end_++;
	printf("22\n");
	var = ft_substr(content, 0, end_);
	while (ft_strncmp(c_env->var, var, end_))
		c_env = c_env->next;
	ft_putstr_fd((char *)c_env->val, fd);
}

void	echo_display(t_double_link_node *node, t_mylist **env, int fd)
{
	int		i;
	char	*content;

	i = 0;
	content = (char *)node->data;
	while (content[i])
	{
		printf("37\n");
		if (content[i] == '$' && content[i + 1] != ' ')
			display_env(fd, env, &content[++i]);
		else
			write(fd, &content[i], 1);
		printf("42\n");
		i++;
	}
}

void	echo_display_opt(t_double_link_node *node, t_mylist **env, int fd)
{
	int		i;
	char	*content;

	i = 0;
	content = (char *)node->data;
	while (content[i])
	{
		printf("56\n");
		if (content[i] == '$' && content[i + 1] != ' ')
		{
			i++;
			display_env(fd, env, &content[i]);
		}
		else
			write(fd, &content[i], 1);
		printf("64\n");
		i++;
	}
	write(fd, "\%", 1);
}

void	next_arg_display(t_double_link_node *node)
{
	if (node->next)
	{
		if (((t_token *)node->data)->type == REDIRECTION)
			node = node->next->next;
		else if (((t_token *)node->data)->type == ARG)
			node = node->next;
		else
			node = NULL;
	}
}

void	ft_echo(t_double_link_node *node_orig, t_mylist **env, int fd)
{
	t_double_link_node	*node;

	node = node_orig;
	if (!node->next)
		return (ft_putstr_fd("\n", fd));
	node = node->next;
	if (is_option(node))
	{
		// node = node->next;
		while (node)
		{
			echo_display_opt(node, env, fd);
			next_arg_display(node);
		}
	}
	else
	{
		while (node)
		{
			echo_display(node, env, fd);
			next_arg_display(node);
		}
	}
}



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

// void	ft_echo(char **msg)
// {
// 	int	option_n;
// 	int	i;

// 	i = 0;
// 	option_n = 0;
// 	if (is_option(msg[0]))
// 	{
// 		i++;
// 		option_n = 1;
// 	}
// 	while (msg[i])
// 	{
// 		ft_printf("%s", msg[i]);
// 		if (msg[i + 1] != NULL)
// 			ft_printf(" ");
// 		i++;
// 	}
// 	if(!option_n)
// 		ft_printf("\n");

// }

// int	main(void)
// {
// 	char	*test[4];
// 	test[0] = "-n";
// 	test[1] = "hello";
// 	test[2] = "word";
// 	test[3] = NULL;
// 	int i = is_option(test[0]);

// 	ft_printf("%d\n", i);
// 	ft_echo(test);
// 	ft_echo(test);

// 	return (0);
// }
