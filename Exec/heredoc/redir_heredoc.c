#include "./../exec.h"

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
	char	c;

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

int main(int ac , char **av)
{
	int k = heredoc(av[1]);
	close (k);
}

