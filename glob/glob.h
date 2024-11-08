#ifndef GLOB_H
# define GLOB_H

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include "../../42_MyLibC/mylibc.h"


typedef struct s_glob
{
	void			*file;
	struct s_glob	*next;
}	t_glob;

int		globbing(const char *str, const char *glob);
t_glob	*glob(const char *pattern);
int		match( const char *str, const char *glob);

#endif
