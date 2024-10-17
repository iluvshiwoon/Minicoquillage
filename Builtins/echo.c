#include "../Tokenizer/Tokenizer.h"
#include "./builtins.h"



// int	is_option(t_double_link_node *node)
// {
// 	if (((t_token *)node->data)->type == OPTION)
// 		return (1);
// 	return (0);
// }

// char	*display_env(int fd, t_mylist **env, char *content)
// {
// 	t_mylist	*c_env;
// 	int			end_;
// 	char		*var;

// 	c_env = *env;
// 	end_ = 0;
// 	while (content[end_] != ' ' && content[end_] != 0 && content[end_] != '\n')
// 		end_++;
// 	var = ft_substr(content, 0, end_);
// 	while (c_env && ft_strncmp(c_env->var, var, end_))
// 		c_env = c_env->next;
// 	free(var);
// 	if (!c_env)
// 		return (NULL);
// 	else
// 		return (ft_putstr_fd((char *)c_env->val, fd), content + end_);
// }

// int is_quote(int in_quote, char c, char *content)
// {
// 	int	i;

// 	i = 0;
// 	if (content[i] == c)
// 	{
// 		while (content[++i])
// 		{
// 			if (content[i] == c)
// 				return (1);
// 		}
// 	}
// 	return (-1);
// }


// void	echo_display(t_double_link_node *node, t_mylist **env, int fd)
// {
// 	int		i;
// 	char	*content;
// 	char	*expanded_content;
// 	int		in_quote;

// 	in_quote = 0;
// 	content = ((t_token *)node->data)->value;
// 	i = 0;
// 	if (((t_token *)node->data)->type == OPTION)
// 		return ;
// 	else
// 	{
// 		while (content[i])
// 		{
// 			// if(content[i] == '\"')
// 			// 	in_quote += is_quote(in_quote, '\"', &content[i]);
// 			// printf("in_quote: %d\n", in_quote);
// 			if (content[i] == '$' && in_quote != 0)
// 			{
// 				expanded_content = display_env(fd, env, content + i + 1);
// 				if (expanded_content)
// 				{
// 					content = expanded_content;
// 					i = 0;
// 				}
// 				else
// 				{
// 					write(fd, &content[i], 1);
// 					i++;
// 				}
// 			}
// 			else
// 			{
// 				write(fd, &content[i], 1);
// 				i++;
// 			}
// 		}
// 	}
// }

// // void	echo_display(t_double_link_node *node, t_mylist **env, int fd)
// // {
// // 	int		i;
// // 	char	*content;

// // 	i = 0;
// // 	content = ((t_token *)node->data)->value;
// // 	while (content[i])
// // 	{
// // 		write(fd, &content[i], 1);
// // 		i++;
// // 	}
// // }

// void	echo_display_opt(t_double_link_node *node, t_mylist **env, int fd)
// {
// 	int				i;
// 	char			*content;
// 	t_token_type	type;

// 	i = 0;
// 	content = ((t_token *)node->data)->value;
// 	type = ((t_token *)node->data)->type;
// 	if (type == OPTION)
// 		return ;
// 	else
// 	{
// 		while (content[i])
// 		{
// 			write(fd, &content[i], 1);
// 			i++;
// 		}
// 	}
// }

// t_double_link_node	*next_arg_display(t_double_link_node *node)
// {
// 	if (node->next)
// 	{
// 		if (((t_token *)node->data)->type == REDIRECTION)
// 			return node->next->next;
// 		else if (((t_token *)node->data)->type == OPTION)
// 			return node->next;
// 		else if (((t_token *)node->data)->type == ARG)
// 			return node->next;
// 		else
// 			return NULL;
// 	}
// 	return NULL;
// }

// void	ft_echo(t_double_link_node *node_orig, t_mylist **env, int fd)
// {
// 	t_double_link_node	*node;

// 	node = node_orig;
// 	if (!node->next)
// 		return (ft_putstr_fd("\n", fd));
// 	node = node->next;
// 	if (is_option(node))
// 	{
// 		node = node->next;
// 		while (node)
// 		{
// 			if (((t_token *)node->data)->type == ARG)
// 			{
// 				echo_display(node, env, fd);
// 				if (node)
// 					write(fd, " ", 1);
// 			}
// 			node = next_arg_display(node);
// 		}
// 	}
// 	else
// 	{
// 		while (node)
// 		{
// 			echo_display(node, env, fd);
// 			node = next_arg_display(node);
// 			if (node)
// 				write(fd, " ", 1);
// 			else
// 				write(fd, "\n", 1);
// 		}
// 	}
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
