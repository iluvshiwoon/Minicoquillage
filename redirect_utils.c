/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:41:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/03 15:31:03 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minicoquillage.h"

int	__stdin(t_mini *mini, t_exec *exec, t_atom *atom, char *globbed)
{
	if (access(globbed, F_OK))
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: No such file or directory\n",
				&exec->skip, &mini->status, globbed), 1);
	else if (access(globbed, R_OK))
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: Permission denied\n",
				&exec->skip, &mini->status, globbed), 1);
	else if (!atom->std_in[exec->j + 1] && atom->heredoc == false)
		atom->in_fd = m_open(mini, globbed, O_RDONLY, 0);
	return (0);
}

int	_stdin(t_mini *mini, t_expanded *expanded, t_atom *atom, t_exec *exec)
{
	char	*globbed;
	t_glob	*_globbed;

	if (expanded->value[exec->j])
	{
		if (_count_glob(mini, expanded->value[exec->j],
				expanded->litteral[exec->j]) > 1)
			return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO),
				_error("minicoquillage: % s : ambiguous redirect\n ",
					&exec->skip, &mini->status, expanded->value[exec->j]), 1);
		else
		{
			_globbed = glob(mini, expanded->value[exec->j],
					expanded->litteral[exec->j]);
			globbed = expanded->value[exec->j];
			if (_globbed)
				globbed = _globbed->file;
		}
		if (__stdin(mini, exec, atom, globbed) == 1)
			return (1);
	}
	return (0);
}

int	__stdout(t_mini *mini, t_atom *atom, t_exec *exec, char *globbed)
{
	struct stat	sb;

	if (stat(globbed, &sb) == -1 && errno == EACCES)
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: Permission denied\n",
				&exec->skip, &mini->status, globbed), 1);
	else if (stat(globbed, &sb) == -1 && errno == ENOENT)
		atom->out_fd = m_open(mini, globbed, O_EXCL | O_CREAT,
				S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
	else if (access(globbed, W_OK))
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: Permission denied\n",
				&exec->skip, &mini->status, globbed), 1);
	else if (S_ISDIR(sb.st_mode))
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: Is a directory\n",
				&exec->skip, &mini->status, globbed), 1);
	else if (access(globbed, W_OK) == 0 && atom->append[exec->i] == false)
		atom->out_fd = m_open(mini, globbed, O_WRONLY | O_TRUNC, 0);
	return (0);
}

int	__stdout1(t_mini *mini, t_atom *atom, t_exec *exec, char *globbed)
{
	if (atom->out_fd == -1)
	{
		if (errno == ENOENT)
			return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO),
				_error("minicoquillage: %s: No such file or dir\
ectory\n", &exec->skip, &mini->status, globbed), 1);
		error_exit(strerror(errno), mini);
	}
	if (atom->out_fd)
		m_dup2(mini, atom->out_fd, STDOUT_FILENO);
	return (0);
}

int	_stdout(t_mini *mini, t_expanded *expanded, t_atom *atom, t_exec *exec)
{
	char	*globbed;
	t_glob	*_globbed;

	if (_count_glob(mini, expanded->value[exec->i],
			expanded->litteral[exec->i]) > 1)
		return (m_dup2(mini, exec->og_stdout, STDOUT_FILENO), _error("m\
inicoquillage: %s: ambiguous redirect\n",
				&exec->skip, &mini->status, expanded->value[exec->i]), 1);
	else
	{
		_globbed = glob(mini, expanded->value[exec->i],
				expanded->litteral[exec->i]);
		globbed = expanded->value[exec->i];
		if (_globbed)
			globbed = _globbed->file;
	}
	if (__stdout(mini, atom, exec, globbed))
		return (1);
	if (!expanded->value[exec->i + 1])
		__red(mini, globbed, atom, exec);
	if (__stdout1(mini, atom, exec, globbed))
		return (1);
	return (0);
}
