/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:37:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/26 11:40:46 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

char	*__get_path(t_heap *heap, char **path, int *status, char *cmd)
{
	int		i;
	char	*r_value;

	i = -1;
	while (path[++i])
	{
		r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, path[i],
				"/");
		r_value = mini_ft_strjoin(heap->heap_allocated, heap->list, r_value,
				cmd);
		if (access(r_value, F_OK) == 0)
		{
			if (is_dir(r_value))
				return (*status = 126, NULL);
			else if (access(r_value, X_OK) == 0)
				return (/* *status = 126,  */ r_value);
			return (*status = 126, ft_printf_fd(STDERR_FILENO, "minicoquillage:
					%s: Permission denied\n", r_value), NULL);
		}
	}
	return (*status = 127, ft_printf_fd(STDERR_FILENO, "minicoquillage: %s",
			mini_ft_strjoin(heap->heap_allocated, heap->list, cmd,
				": command not found\n")), NULL);
}

char	*_get_path(t_heap *heap, char **envp, int *status, char *cmd)
{
	int		i;
	char	**path;
	char	*r_value;

	i = -1;
	r_value = _getenv(heap, "PATH", envp, *status);
	if (!r_value)
		return (*status = 127, ft_printf_fd(STDERR_FILENO, "%s",
				mini_ft_strjoin(heap->heap_allocated, heap->list,
					mini_ft_strjoin(heap->heap_allocated, heap->list,
						"minicoquillage: ", cmd),
					": No such file or directory\n")), NULL);
	path = mini_ft_split(heap, r_value, ':');
	while (path[++i])
	{
		r_value = ft_strnstr(path[i], cmd, ft_strlen(path[i]));
		if (r_value && r_value != path[i] && !*(r_value + ft_strlen(cmd)))
		{
			if (access(path[i], X_OK) == 0)
				return (path[i]);
			return (*status = 126, ft_printf_fd(STDERR_FILENO, "minicoquillage:
					%s: Permission denied\n", path[i]), NULL);
		}
	}
	return (__get_path(heap, path, status, cmd));
}

char	*get_path(t_heap *heap, char **envp, int *status, char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!(cmd[0]))
		return (*status = 127, ft_printf_fd(STDERR_FILENO, "minicoquillage: %s",
				mini_ft_strjoin(heap->heap_allocated, heap->list, cmd,
					": command not found\n")), NULL);
	if (is_path(cmd) && access(cmd, F_OK) == -1)
		return (*status = 127, ft_printf_fd(STDERR_FILENO, "%s",
				mini_ft_strjoin(heap->heap_allocated, heap->list,
					mini_ft_strjoin(heap->heap_allocated, heap->list,
						"minicoquillage: ", cmd),
					": No such file or directory\n")), NULL);
	else if (is_path(cmd) && access(cmd, X_OK) == -1)
		return (*status = 126, ft_printf_fd(STDERR_FILENO, "minicoquillage:
				%s: Permission denied\n", cmd), NULL);
	else if (is_path(cmd) && is_dir(cmd))
		return (*status = 126, NULL);
	else if (is_path(cmd) && access(cmd, X_OK) == 0)
		return (cmd);
	return (_get_path(heap, envp, status, cmd));
}
