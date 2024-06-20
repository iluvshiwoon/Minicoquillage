#include "expand.h"

// int	nb_dollar_sign(char *cmd)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '$')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

void	store_quote(t_list *pieces, char *str)
{
	t_variables	*content;
	t_list		*new;
	char		*substr;
	char		*end;

	end = str;
	while (*(end + 1) == ' ')
		end++;
	substr = ft_substr(str, 0, (end - str));
	content->my_str = substr;
	content->is_quote = 1;
	content->is_var = 0;
	content->expand = substr;
	new->content = (t_variables *)content;
	ft_lstadd_back(pieces, new);
	str = ++end;
}

void	store_var(t_list *pieces, char *str)
{
	t_variables	*content;
	t_list		*new;
	char		*substr;
	char		*end;

	end = str;
	while (*(end + 1) != ' ')
		end++;
	while (*(end + 1) == ' ')
		end++;
	substr = ft_substr(str, 0, (end - str));
	content->my_str = substr;
	content->is_quote = 0;
	content->is_var = 1;
	content->expand = extansion(substr[1]);
	new->content = (t_variables *)content;
	ft_lstadd_back(pieces, new);
	str = ++end;
}

void	store_char(t_list *pieces, char *str)
{
	t_variables	*content;
	t_list		*new;
	char		*substr;
	char		*end;

	end = str;
	while (*(end + 1) != ' ')
		end++;
	while (*(end + 1) == ' ')
		end++;
	substr = ft_substr(str, 0, (end - str));
	content->my_str = substr;
	content->is_quote = 0;
	content->is_var = 0;
	content->expand = substr;
	new->content = (t_variables *)content;
	ft_lstadd_back(pieces, new);
	str = ++end;
}

void	store_of_str(t_list **pieces, char *str)
{
	t_list	*tmp;
	char	*substr;
	int		i;

	i = 0;
	substr = str;
	tmp = NULL;
	while (*substr)
	{
		if (*substr == '\"' || *substr == '\'')
			store_quote(tmp, substr);
		else if (*substr == '$')
			store_var(tmp, substr);
		else
			store_char(tmp, substr);
	}
	pieces = &tmp;
}

t_list	*store_str_to_expand(t_list **pieces, char *full_str)
{
	int	nb_vars;

	nb_vars = nb_dollar_sign(full_str);
	store_of_str(pieces, full_str);
	return (nb_vars);
}
