#include "../exec.h"

int	position_pattern(const char *str, const char *pattern)
{
	int		p;
	int		i;
	char	*substr;

	p = ft_strlen(pattern);
	i = 0;
	while (i <= (ft_strlen(str) - p))
	{
		substr = ft_substr(str, i, p);
		if (substr && !ft_strncmp(substr, pattern, p))
		{
			free(substr);
			return (i);
		}
		free(substr);
		i++;
	}
	return (-1);
}

/*
 *exemple glob: *str*
 *exemple str:  -str1
 */
int	glob(char *str, char *glob)
{
	int		i;
	int		sx;
	int		pp;
	char	**patterns;

	i = 0;
	sx = 0;
	pp = 0;
	if (ft_strlen(glob) == 1 && glob[0] == '*')
		return (0);
	patterns = ft_split(glob, '*');
	while (patterns[i])
	{
		ft_printf("%s\n", patterns[i]);
		pp = position_pattern((const char *)&str[sx], patterns[i]);
		if (pp >= 0)
		{
			sx = pp + ft_strlen(patterns[i]);
			i++;
		}
		else
			return (0);
	}
	return (1);
}



int	main(void)
{
	ft_printf("position %d\n", position_pattern("un truc", "un"));
	ft_printf("glob %d\n", glob("untruc", "*u8*n*c"));
}
