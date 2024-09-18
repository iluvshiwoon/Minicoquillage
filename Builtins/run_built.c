#include "./builtins.h"
#include "../Tokenizer/Tokenizer.h"


int	run_built(t_double_link_node *node_orig, t_mylist **env)
{
	t_token				*input;
	t_double_link_node	*node;
	int					fd;

	node = node_orig;
	input = (t_token *)node->data;
	if (ft_strncmp(input->value, "echo", 5))
		return (ft_echo(node, env, 1), 0);
	if (ft_strncmp(input->value, "env", 4))
		return (put_envc(*env), 0);

	return (1);
}

