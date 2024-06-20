#ifndef EXPAND_H
# define EXPAND_H

# include "./../exec.h"

typedef struct s_variables
{
	char	*my_str;
	int		is_quote;
	int		is_var;
	char	*expand;
}	t_variables;

int		nb_dollar_sign(char *cmd);
t_list	*store_str_to_expand(t_list **pieces, char *full_str);


#endif
