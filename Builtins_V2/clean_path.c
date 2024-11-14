#include "./builtins.h"


static int	is_absolute(char *vpath)
{
	int		i;
	char	**split_path;

    i = 0;
	split_path = ft_split(vpath, '/');
	while (split_path[i])
	{
		if (ft_strncmp(split_path[i], ".", 2) == 0)
			return (1);
		if (ft_strncmp(split_path[i], "..", 2) == 0)
			return (1);
		if (ft_strncmp(split_path[i], "~", 1) == 0)
			return (1);
		i++;
	}
	//ft_free(split_path);
	return (0);

}


t_double_link_list	*add_to_root(t_double_link_list *root, char *value)
{
	t_double_link_node	*pwd;

	pwd = (t_double_link_node *)malloc(sizeof(t_double_link_node));
	if (!pwd)
		return (NULL);
	pwd->data = (char *)value;
	pwd->next = NULL;
	if (root->first_node == NULL)
	{
		root->first_node = pwd;
	}
	else
		insert_end(root, pwd);
	return (root);
}



t_double_link_list	*init_root_pwd(t_double_link_list *l_pwd, char *vpath, t_mylist *curpath)
{
	char				**split_vpath;
	char				**split_curpath;
	int					i;

	i = 0;
	split_vpath = ft_split(vpath, '/');
	split_curpath = ft_split(curpath->val, '/');
	if (ft_strncmp(split_vpath[0], ".", 2) == 0)
	{
		while (split_curpath[i])
		{
			add_to_root(l_pwd, split_curpath[i]);
			i++;
		}
	}
	i = 0;
	while (split_vpath[i])
	{
		add_to_root(l_pwd, split_vpath[i]);
		i++;
	}
	return (l_pwd);
}

char	*to_absolute(char *vpath, t_mylist *curpath)
{
	char				*to_path;
	t_double_link_list	*l_pwd;
	t_double_link_node	*cursor;

	to_path = ft_strdup("");
	l_pwd = (t_double_link_list *)malloc(sizeof(t_double_link_list));
	if (!l_pwd)
		return (NULL);
	l_pwd = init_root_pwd(l_pwd, vpath, curpath);
	cursor = l_pwd->last_node->previous;
	while (cursor)
	{
		if (ft_strncmp((char *)cursor->data, ".", 2) == 0)
			;
		else if(ft_strncmp((char *)cursor->data, "..", 3) == 0)
		{
			cursor = cursor->previous;
		}
		else if(ft_strncmp((char *)cursor->data, "~", 2) == 0)
		{
			if (cursor->previous == NULL)
			{
				to_path = ft_strjoin(cursor->data, to_path);
				to_path = ft_strjoin("/", to_path);
			}
			else
				return (NULL);
		}
		else
		{
			to_path = ft_strjoin(cursor->data, to_path);
			to_path = ft_strjoin("/", to_path);
		}
		cursor = cursor->previous;
	}
	return (to_path);
}

char	*my_vpath(char *vpath, t_mylist *curpath)
{
	int		type_path;
	char	*to_path;

	type_path = is_absolute(vpath);
	if (type_path == 0)
	{
		return (vpath);
	}
	else
	{
		to_path = ft_strdup(to_absolute(vpath, curpath));
		return (to_path);
	}
}
