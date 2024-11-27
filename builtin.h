/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:33:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/27 21:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# ifndef MINICOQUILLAGE_H
#  include "minicoquillage.h"
# endif

int		mini_pwd(void);
int		mini_echo(char **args);
int		mini_env(char **envp);
int		mini_exit(t_mini *mini, char **args, t_exec exec);
int		mini_export(t_heap *heap, char **args, char ***envp);
int		mini_unset(t_heap *heap, char **args, char ***envp);
int		mini_cd(t_heap *heap, char **args, char ***envp);
void	__print_cd(char **path, t_heap *heap, char **envp);
void	f_export(t_heap *heap, char ***envp, char *var, char *value);
int		_var_name_cmp(char *s1, char *s2);
int		_search_var(t_heap *heap, char *arg, char **env);

#endif
