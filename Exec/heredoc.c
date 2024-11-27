/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:32:45 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 17:24:48 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	open_heredoc(t_heap *heap, t_atom *atom)
{
	static int	i;
	char		*tmp;
	char		*nb;

	tmp = "/tmp/tmp_file";
	if (access("/tmp", F_OK) != EXIT_SUCCESS)
		error_exit("/tmp directory doesn't exist!\n", heap->heap_allocated);
	else if (access("/tmp", R_OK | W_OK) != EXIT_SUCCESS)
		error_exit("Wrong permission for /tmp directory\n",
			heap->heap_allocated);
	nb = ft_itoa(i++);
	tmp = mini_ft_strjoin(heap->heap_allocated, heap->list, tmp, nb);
	free(nb);
	if (access(tmp, F_OK) == EXIT_SUCCESS)
		unlink(tmp);
	atom->in_fd = open(tmp, O_RDWR | O_EXCL | O_CREAT, S_IRUSR | S_IWUSR);
	if (atom->in_fd == -1)
		return (perror(NULL), error_exit("open failed\n",
				heap->heap_allocated));
	atom->file_heredoc = tmp;
}

int	listen_heredoc(t_heap *heap, int *fd, char *eof)
{
	char	*line;
	int		i;
	int		_stdin;

	i = 0;
	_stdin = dup(STDIN_FILENO);
	eof = _quote(heap, eof);
	while (g_signal != SIGINT && ++i)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (dup2(_stdin, 0), _close(_stdin), free(line), 0);
		_close(_stdin);
		if (!line)
			return (ft_printf_fd(STDERR_FILENO, "minicoquillage: warning: \
here-document at line %d delimited by \
end-of-file (wanted `%s')\n", i, eof), free(line), 0);
		else if (strncmp(eof, line, _max_len(ft_strlen(eof),
					ft_strlen(line))) == EXIT_SUCCESS)
			return (free(line), 0);
		else if (*fd)
			_write_listen(heap, *fd, line);
		free(line);
	}
	return (_close(_stdin), 0);
}

void	run_heredoc(t_heap *heap, t_atom *atom)
{
	int	i;

	i = -1;
	while (atom->heredoc_eof[++i])
	{
		if (g_signal == SIGINT)
			break ;
		if (atom->heredoc && atom->heredoc_eof[i + 1] == NULL)
			open_heredoc(heap, atom);
		listen_heredoc(heap, &atom->in_fd, atom->heredoc_eof[i]);
	}
}

void	heredoc(t_heap *heap, t_ast_node *first_node)
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
			heredoc(heap, left);
		else
			run_heredoc(heap, p_node->atom);
		p_node = first_node->data;
		if (p_node->ops)
		{
			if (p_node->atom)
				run_heredoc(heap, p_node->atom);
		}
		first_node = first_node->right;
	}
}
