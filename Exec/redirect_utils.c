/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:41:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 15:42:07 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_error(char *error, int *skip, int *status, char *filename,
		int err_status)
{
	*skip = 1;
	*status = err_status;
	ft_printf_fd(STDERR_FILENO, error, filename);
}

int	_stdin(t_heap *heap, int *skip, int *status, t_expanded *expanded, int i,
		t_atom *atom, int og_stdout)
{
	char	*globbed;
	t_glob	*_globbed;

	if (expanded->value[i])
	{
		if (_count_glob(heap, expanded->value[i], expanded->litteral[i]) > 1)
			return (dup2(og_stdout, STDOUT_FILENO),
					_error("minicoquillage:
								% s
							: ambiguous redirect\n ", skip, status,
								expanded->value[i],
								1),
					1);
		else
		{
			_globbed = glob(heap, expanded->value[i], expanded->litteral[i]);
			globbed = expanded->value[i];
			if (_globbed)
				globbed = _globbed->file;
		}
		if (access(globbed, F_OK))
			return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
					%s: No such file or directory\n", skip, status, globbed, 1),
				1);
		else if (access(globbed, R_OK))
			return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
					%s: Permission denied\n", skip, status, globbed, 1), 1);
		else if (!atom->std_in[i + 1] && atom->heredoc == false)
			atom->in_fd = open(globbed, O_RDONLY);
	}
	return (0);
}

int	_stdout(t_heap *heap, int *skip, int *status, t_expanded *expanded, int i,
		t_atom *atom, int og_stdout)
{
	char		*globbed;
	t_glob		*_globbed;
	struct stat	sb;

	if (_count_glob(heap, expanded->value[i], expanded->litteral[i]) > 1)
		return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
				%s: ambiguous redirect\n", skip, status, expanded->value[i], 1),
			1);
	else
	{
			_globbed = glob(heap, expanded->value[i], expanded->litteral[i]);
			globbed = expanded->value[i];
			if (_globbed)
				globbed = _globbed->file;
	}
	if (stat(globbed, &sb) == -1 && errno == EACCES)
		return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
				%s: Permission denied\n", skip, status, globbed, 1), 1);
	else if (stat(globbed, &sb) == -1 && errno == ENOENT)
	{
			atom->out_fd = open(globbed, O_EXCL | O_CREAT,
					S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
			_close(atom->out_fd);
	}
	else if (access(globbed, W_OK))
		return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
				%s: Permission denied\n", skip, status, globbed, 1), 1);
	else if (S_ISDIR(sb.st_mode))
		return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
				%s: Is a directory\n", skip, status, globbed, 1), 1);
	else if (access(globbed, W_OK) == 0 && atom->append[i] == false)
	{
			atom->out_fd = open(globbed, O_WRONLY | O_TRUNC);
			_close(atom->out_fd);
	}
	if (!expanded->value[i + 1])
	{
			if (atom->append[i])
				atom->out_fd = open(globbed, O_WRONLY | O_APPEND);
			else
				atom->out_fd = open(globbed, O_WRONLY);
	}
	if (atom->out_fd == -1)
	{
			if (errno == ENOENT)
			return (dup2(og_stdout, STDOUT_FILENO), _error("minicoquillage:
					%s: No such file or directory\n", skip, status, globbed, 1),
				1);
		perror("open"); // FIXME redirection fail ? skip ?
	}
	if (atom->out_fd)
		dup2(atom->out_fd, STDOUT_FILENO);
	return (0);
}
