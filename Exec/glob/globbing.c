#include "../exec.h"

int	position_pattern(const char *str, const char *pattern)
{
	int		p;
	int		i;
	char	*substr;

	p = ft_strlen(pattern);
	i = 0;
	if (p == 1 && pattern[0] == '*')
		return (0);
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
 *exemple glob: str*hj
 *exemple str:  -str1strhj
 */
int	glob(char *str, char *glob)
{
	int		i;
	int		sx;
	int		pp;
	char	**patterns;
	int		len_patt;

	i = 0;
	sx = 0;
	pp = 0;
	patterns = ft_split(glob, '*');
	len_patt = ft_strlen(patterns[0]);
	if (str[i] != '*' && !ft_strncmp(str, patterns[i], len_patt))
	{
		i++;
		sx = len_patt;
	}
	else if (str[i] != '*' && ft_strncmp(str, patterns[i], len_patt))
		return (0);
	while (patterns[i])
	{
		pp = position_pattern((const char *)&str[sx], patterns[i]);
		if (pp > 0)
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
	ft_printf("position %d\n", position_pattern("un truc", "tr"));
	ft_printf("glob %d\n", glob("un truc", "un t*c"));
}
