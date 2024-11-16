#ifndef BUILTIN_H
# define BUILTIN_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

int	mini_pwd(void);
int mini_echo(char **args);
int	mini_exit(char **args);
int mini_env(char ** envp);
int mini_export(t_heap * heap, char ** args, char *** envp);
int mini_unset(t_heap * heap, char ** args, char *** envp);
int mini_cd(t_heap * heap, char ** args, char *** envp);

#endif
