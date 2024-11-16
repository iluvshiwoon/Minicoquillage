#ifndef GLOB_H
# define GLOB_H
#ifndef MINICOQUILLAGE_H
# include "../Minicoquillage.h"
#endif

typedef struct s_glob
{
	void			*file;
	struct s_glob	*next;
}	t_glob;

int		globbing(const char *str, const char *glob);
t_glob	*glob(t_heap * heap, const char *pattern, bool * litteral);
int match( const char *str, const char *glob, bool * litteral);
#endif