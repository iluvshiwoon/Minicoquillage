#include "./../exec.h"

// int is_infile(char *infile)
// {
// 	if (!ft_strcmp(infile, "<"))
// 		return (1);
// 	return (0);
// }


// char	*infile_name(char **context, int position)
// {
// 	int	i;

// 	i = position;
// 	while (context[i][0] != '|')
// 	{
// 		if (is_infile(context[i]))
// 			return (context[i + 1]);
// 		i++;
// 	}
// 	return (NULL);
// }


// int	check_O(char *buff, char *limiter)
// {
// 	int i = 0;
// 	char *start = buff;

// 	while (*start)
// 		start++;
// 	start = start - ft_strlen(limiter) - 1;
// 	if (*start == '\n')
// 		start++;
// 	else
// 		return (0);
// 	while (start[i])
// 	{
// 		if (start[i] == limiter[i])
// 			i++;
// 		else
// 			return(0);
// 	}
// 	return (i);
// }


// int	heredoc_O(char *limiter)
// {
// 	int i = 0;
// 	char buff[1024];
// 	char *c = buff;
// 	int hd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC);
// 	// int hd = open("/tmp/.heredoc", O_CREAT | O_TRUNC);
// 	int run = 1;
// 	int stop = 0;

// 	while (run)
// 	{
// 		read(1, c, 1);
// 		if (!stop && *c != limiter[ft_strlen(limiter) - 1])
// 		// if (*c != 't')
// 		{
// 			ft_putchar_fd(*c, hd);
// 			c++;
// 			i++;
// 			stop = check(&buff[0], limiter);
// 		}
// 		else
// 		{
// 			write(1, buff, i);
// 			run = 0;
// 		}
// 	}
// 	return (hd);
// }


void	put_in_fd(char *buff, int hd)
{
	char	*current;
	int		len;

	len = ft_strlen(buff);
	current = buff;
	write(hd, current, len);
	buff = ft_calloc(len, sizeof(char));
}

void	write_fd(int fd)
{
	char	c;
	int		n;

	n = read(fd, &c, 1);
	while (n > 0)
	{
		write(1, &c, 1);
		n = read(fd, &c, 1);
	}
}

int heredoc(char *limiter)
{
	char	*buff;
	int		hd;
	char c;

	hd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC);
	if (hd < 0)
		ft_putstr_fd("ohoh", 1);
	write(1, "heredoc> ", 9);
	buff = get_next_line(0);
	while (buff)
	{
		if (!ft_strncmp((buff), limiter, ft_strlen(limiter)))
		{
			free(buff);
			break;
		}
		ft_putstr_fd(buff, hd);
		write(1, "heredoc> ", 9);
		free(buff);
		buff = get_next_line(0);
	}
	hd = open("heredoc", O_RDONLY);
	write_fd(hd);
	return (hd);
}

int main()
{
	int k = heredoc("toto");
	close (k);
}

