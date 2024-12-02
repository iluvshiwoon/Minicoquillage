/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:32:45 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 22:56:51 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

void	open_heredoc(t_mini *mini, t_atom *atom)
{
	static int	i;
	char		*tmp;
	char		*nb;

	tmp = "/tmp/tmp_file";
	if (access("/tmp", F_OK) != EXIT_SUCCESS)
		error_exit("/tmp directory doesn't exist!\n",mini);
	else if (access("/tmp", R_OK | W_OK) != EXIT_SUCCESS)
		error_exit("Wrong permission for /tmp directory\n", mini);
	nb = ft_itoa(i++);
	tmp = mini_ft_strjoin(mini, tmp, nb);
	free(nb);
	if (access(tmp, F_OK) == EXIT_SUCCESS)
		unlink(tmp);
	atom->in_fd = m_open(mini, tmp, O_RDWR | O_EXCL | O_CREAT, S_IRUSR | S_IWUSR);
	atom->file_heredoc = tmp;
}

int	listen_heredoc(t_mini *mini, int *fd, char *eof)
{
	char	*line;
	int		i;
	int		_stdin;

	i = 0;
	_stdin = m_dup(mini,STDIN_FILENO);
	eof = _quote(mini, eof);
	while (g_signal != SIGINT && ++i)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (m_dup2(mini,_stdin, STDIN_FILENO), free(line), 0);
		if (!line)
			return (ft_printf_fd(STDERR_FILENO, "minicoquillage: warning: \
here-document at line %d delimited by \
end-of-file (wanted `%s')\n", i, eof), free(line), 0);
		else if (strncmp(eof, line, _max_len(ft_strlen(eof),
					ft_strlen(line))) == EXIT_SUCCESS)
			return (free(line), 0);
		else if (*fd)
			_write_listen(*fd, line);
		free(line);
	}
	return (0);
}

void	run_heredoc(t_mini *mini, t_atom *atom)
{
	int	i;

	i = -1;
	while (atom->heredoc_eof[++i])
	{
		if (g_signal == SIGINT)
			break ;
		if (atom->heredoc && atom->heredoc_eof[i + 1] == NULL)
			open_heredoc(mini, atom);
		listen_heredoc(mini, &atom->in_fd, atom->heredoc_eof[i]);
	}
}

void	heredoc(t_mini *mini, t_ast_node *first_node)
{
	t_ast_node		*left;
	t_parser_node	*p_node;

	while (first_node && first_node->left)
	{
		if (g_signal == SIGINT)
			break ;
		left = first_node->left;
		p_node = left->data;
		if (is_op(p_node->ops))
			heredoc(mini, left);
		else
			run_heredoc(mini, p_node->atom);
		p_node = first_node->data;
		if (p_node->ops)
		{
			if (p_node->atom)
				run_heredoc(mini, p_node->atom);
		}
		first_node = first_node->right;
	}
}
