/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:10:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/06/26 15:27:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minicoquillage.h"

void	toggle_quote(int *quote, int *quote1)
{
	if (*quote)
		*quote = 0;
	else if (!(*quote1))
		*quote = 1;
}

char	*wrapper_strjoin_concat(char *s1, char *s2, t_double_link_list *list,
		t_string *string)
{
	char	*r_value;

	r_value = ft_strjoin(s1, s2);
	if (!r_value)
	{
		if (string->dst)
			free(string->dst);
		if (string->temp)
			free(string->temp);
		return (dl_free_list(list), exit(EXIT_FAILURE), r_value);
	}
	return (r_value);
}

void	init_control(t_control_dll *control)
{
	control->list = malloc(sizeof(*control->list));
	control->node = malloc(sizeof(*control->node));
	if (!control->list || !control->node)
		return (free(control->list), free(control->node), exit(EXIT_FAILURE));
	init_list(control->list);
}

char	*init_line(t_control_dll *control, char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (free(control->list), free(control->node), free(prompt),
			free(line), exit(EXIT_FAILURE), NULL);
	control->node->data = line;
	control->list->pf_insert_end(control->list, control->node);
	return (line);
}

char	*update_node(t_control_dll *control, char *prompt, char *line)
{
	control->node = malloc(sizeof(*control->node));
	if (!control->node)
		return (dl_free_list(control->list), free(prompt), free(line),
			exit(EXIT_FAILURE), NULL);
	line = readline("· ");
	if (!control->node)
		return (dl_free_list(control->list), free(prompt), free(line),
			exit(EXIT_FAILURE), NULL);
	control->node->data = line;
	control->list->pf_insert_end(control->list, control->node);
	return (line);
}
