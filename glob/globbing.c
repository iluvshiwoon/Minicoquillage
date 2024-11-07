#include "../exec.h"

int match( const char *str, const char *glob) {
	int	gx;
	int	sx;
	int	lastgx;
	int	nextsx;

	gx = 0;
	sx = 0;
	lastgx = -1;
	nextsx = 0;
	while (gx < strlen(glob) || sx < strlen(str))
	{
		if (gx < strlen(glob))
		{
			char c = glob[gx];
			if (c == '*')
			{
				lastgx = gx;
				nextsx = sx + 1;
				gx++;
				continue;
			}
			else
			{
				if (sx < strlen(str) && str[sx] == c)
				{
					gx++;
					sx++;
					continue;
				}
			}
		}
		if (nextsx > 0 && nextsx <= strlen(str))
		{
			gx = lastgx;
			sx = nextsx;
			continue;
		}
		return (0);
	}
	return (1);
}



// int	position_pattern(const char *str, const char *pattern)
// {
// 	int		p;
// 	int		i;
// 	char	*substr;

// 	p = ft_strlen(pattern);
// 	i = 0;
// 	while (i <= (ft_strlen(str) - p))
// 	{
// 		substr = ft_substr(str, i, p);
// 		if (substr && !ft_strncmp(substr, pattern, p))
// 		{
// 			free(substr);
// 			return (i);
// 		}
// 		else
// 		{
// 		free(substr);
// 		i++;

// 		}
// 	}
// 	return (-1);
// }

// int	single_case(char **patterns)
// {
// 	int	i;

// 	i = 0;
// 	while (patterns[i])
// 		i++;

// 	if (i == 1 && ft_strlen(patterns[0]) == 1)
// 		return (1);
// 	return (0);
// }


// int	result(char **patterns, const char *glob, const char *str, int i)
// {
// 	int	a;

// 	a = ft_strlen(patterns[i - 1]);
// 	if (glob[ft_strlen(glob) - 1] != '*'
// 		&& patterns[i - 1][a - 1] != str[ft_strlen(str) - 1])
// 		return (0);
// 	return (1);
// }

// /**
//  *glob - function that compare a string with a pattern
//  *@glob: *str* exemple of pattern acceped
//  *@str:  -str1 exemple a string to compare
//  *Return: 0 if the string is not accepted by the pattern,  else 1
//  *To Free:
//  *		-none
//  */
// int	globbing(const char *str, const char *glob)
// {
// 	int		i;
// 	int		sx;
// 	int		pp;
// 	char	**patterns;

// 	i = 0;
// 	sx = 0;
// 	pp = 0;
// 	if (ft_strlen(glob) == 1 && glob[0] == '*')
// 		return (1);
// 	patterns = ft_split(glob, '*');
// 	if (single_case(patterns))
// 		return (0);
// 	while (patterns[i])
// 	{
// 		pp = position_pattern(&str[sx], patterns[i]);
// 		if (pp >= 0)
// 		{
// 			sx = pp + ft_strlen(patterns[i]);
// 			i++;
// 		}
// 		else
// 			return (0);
// 	}
// 	return (result(patterns, glob, str, i));
// }



// int	main(int ac, char **av)
// {
// 	printf("%d\n", globbing(av[1], av[2]));
// 	return globbing(av[1], av[2]);
// }




