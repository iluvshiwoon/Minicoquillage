#include "../Minicoquillage.h"

void put_glob(t_glob *head, int fd)
{
	t_glob *tmp;
	char *str;

	tmp = head;
	while (tmp != NULL)
	{
		str = (char *)tmp->file;
		ft_putstr_fd(str, fd);
		if(tmp->next != NULL)
			ft_putchar_fd(' ', fd);
		tmp = tmp->next;
	}
}

int	max_file(void)
{
	const char *path;
	DIR *dir;
	struct dirent *entry;
	int i;

	i = 0;
	path = ".";
	dir = opendir(path);
	if (dir == NULL)
		return 0;
	while ((entry = readdir(dir)) != NULL)
		i++;
	closedir(dir);
	return (i);
}

char **store_tmp(t_heap * heap, int size)
{
	const char *path;
	DIR *dir;
	struct dirent *entry;
	char **tmp;

	tmp = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char *) * (size + 1));
	path = ".";
	dir = opendir(path);
	if (dir == NULL)
		return 0;
	while ((entry = readdir(dir)) != NULL)
	{
		*tmp = mini_ft_strdup(heap->heap_allocated, heap->list, entry->d_name);
		tmp++;
	}
	*tmp = NULL;
	closedir(dir);
	return (tmp - size);
}

t_glob	*store_match(t_heap * heap,char **tmp, const char *pattern, bool * litteral, t_glob *head_glob)
{
	t_glob *new;
	t_glob *head_empty;
	int i;

	i = 0;
	head_empty = head_glob;
	while (tmp[i] != NULL)
	{
		if (match(tmp[i], pattern, litteral)
			&& ft_strncmp(tmp[i], ".", ft_strlen(tmp[i]) + 1) != 0
			&& ft_strncmp(tmp[i], "..", ft_strlen(tmp[i]) + 1) != 0
			&& tmp[i][0] != '.')
		{
			new = wrap_malloc(heap->heap_allocated, heap->list, sizeof(t_glob));
			if (new == NULL)
				return head_glob;
			new->file = mini_ft_strdup(heap->heap_allocated, heap->list,tmp[i]);
			new->next = head_glob->next;
			head_glob->next = new;
		}
		i++;
	}
	head_glob = head_empty->next;
	return head_glob;
}

t_glob	*store_hidden(t_heap * heap, char **tmp, const char *pattern, bool * litteral, t_glob *head_glob)
{
	t_glob *new;
	t_glob *head_empty;
	int i;

	i = 0;
	head_empty = head_glob;
	while (tmp[i] != NULL)
	{
		if (match(tmp[i], pattern, litteral)
			&& ft_strncmp(tmp[i], ".", ft_strlen(tmp[i]) + 1) != 0
			&& ft_strncmp(tmp[i], "..", ft_strlen(tmp[i]) + 1) != 0
			&& tmp[i][0] == '.')
		{
			new = wrap_malloc(heap->heap_allocated, heap->list,sizeof(t_glob));
			if (new == NULL)
				return head_glob;
			new->file = mini_ft_strdup(heap->heap_allocated, heap->list,tmp[i]);
			new->next = head_glob->next;
			head_glob->next = new;
		}
		i++;
	}
	head_glob = head_empty->next;
	free(head_empty);
	return head_glob;
}

t_glob	*glob(t_heap * heap, const char *pattern, bool * litteral)
{
	t_glob *head_glob;
	char **tmp;
	int size;

	size = max_file();
	tmp = store_tmp(heap, size);
	head_glob = wrap_malloc(heap->heap_allocated, heap->list, sizeof(t_glob));
	if (head_glob == NULL)
		return NULL;
	head_glob->file = NULL;
	head_glob->next = NULL;
	if (pattern[0] == '.')
		head_glob = store_hidden(heap, tmp, pattern,litteral, head_glob);
	else
		head_glob = store_match(heap, tmp, pattern,litteral, head_glob);
	return head_glob;
}

// int main (int ac, char **av)
// {
//
// 	t_glob	*head;
// 	const char *pattern;
//
// 	if (ac != 2)
// 		return EXIT_FAILURE;
// 	pattern = (const char *)av[1];
// 	head = glob(av[1]);
// 	put_glob(head, 1);
//
// 	return EXIT_SUCCESS;
// }