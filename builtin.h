/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:33:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/12/02 21:24:41 by kgriset          ###   ########.fr       */
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
int		mini_exit(t_mini *mini, char **args);
int		mini_export(t_mini *mini, char **args);
int		mini_unset(t_mini *mini, char **args);
int		mini_cd(t_mini *mini, char **args);
void	__print_cd(t_mini *mini, char **path);
void	f_export(t_mini *mini, char *var, char *value);
int		_var_name_cmp(char *s1, char *s2);
int		_search_var(t_mini *mini, char *arg);

#endif
