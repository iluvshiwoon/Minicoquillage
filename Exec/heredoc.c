/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:32:45 by kgriset           #+#    #+#             */
/*   Updated: 2024/11/25 11:42:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void here_assign(char * to_expand, char * expanded)
{
    int j;
    int l;
    t_open_quote open;

    open.double_quote = 0;
    open.single_quote = 0;
    j = -1;
    l = -1;
    while (to_expand[++j])
    {
        if (_handle_quote(to_expand[j], &open) == EXIT_SUCCESS);
        else if (to_expand[j] == '"' && open.double_quote)
            open.double_quote = 0;
        else if (to_expand[j] == '\'' && open.single_quote)
            open.single_quote = 0;
        else
            expanded[++l] = to_expand[j];
        if (!to_expand[j])
            break;
    }
}

int here_count(char * str)
{
    int i;
    int count;
    t_open_quote open;

    i = -1;
    count = 0;
    open.double_quote = 0;
    open.single_quote = 0;
    while(str[++i])
    {
        if (_handle_quote(str[i], &open) == EXIT_SUCCESS);
        else if (str[i] == '"' && open.double_quote)
            open.double_quote = 0;
        else if (str[i] == '\'' && open.single_quote)
            open.single_quote = 0;
        else
            ++count;
        if (!str[i])
            break;
    }
    return count;
}

bool here_is_empty_quote(char * to_expand)
{
    if (to_expand[0] == '\'' || to_expand[0] == '"')
    {
        if (to_expand[1] == to_expand[0])
            return true;
    }    
    return false;
}

char * _quote(t_heap * heap, char * to_expand)
{
    char * expanded;
    int i;
    int count;

    i = -1;
    expanded = NULL;
    while (to_expand[++i])
    {
        count = here_count(to_expand);
        if (!count && here_is_empty_quote(to_expand))
        {
            expanded = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char));
            expanded[0] = '\0';
        }
        else if (count)
        {
            expanded = wrap_malloc(heap->heap_allocated, heap->list, sizeof(char) * (count + 1));
            expanded[count] = '\0';
            here_assign(to_expand,expanded);
        }
    }
    return (expanded);
}

void mini_write(t_heap * heap,int fd, char * str, ssize_t bytes)
{
    ssize_t written;
    size_t offset;

    written = 0;
    offset = 0;
    while(1)
    {
        written = write(fd, str + offset, bytes - offset);
        if (written == -1)
            return(perror(NULL),error_exit("write failed\n",heap->heap_allocated));
        if (written == bytes)
            break;
        offset = written;
    }
}

void    open_heredoc(t_heap * heap, t_atom * atom)    
{
    static int i;
    char * tmp;
    char * nb;

    tmp = "/tmp/tmp_file";
    if (access("/tmp",F_OK) != EXIT_SUCCESS)
        error_exit("/tmp directory doesn't exist!\n", heap->heap_allocated);
    else if (access("/tmp",R_OK | W_OK) != EXIT_SUCCESS)
        error_exit("Wrong permission for /tmp directory\n", heap->heap_allocated);
    nb = ft_itoa(i++);
    tmp = mini_ft_strjoin(heap->heap_allocated,heap->list,tmp,nb);
    free(nb);
    if (access(tmp, F_OK) == EXIT_SUCCESS)
        unlink(tmp);
    atom->in_fd = open(tmp, O_RDWR | O_EXCL | O_CREAT , S_IRUSR | S_IWUSR);
    if (atom->in_fd == -1)
        return(perror(NULL),error_exit("open failed\n", heap->heap_allocated));
    atom->file_heredoc = tmp;
}

size_t _max_len(size_t len1, size_t len2)
{
    if (len1 >= len2)
        return (len1);
    return (len2);
}

void    listen_heredoc(t_heap * heap, int * fd, char * eof)
{
    char * line;
    int i;
    int _stdin;
    
    i = 0;
    _stdin = dup(STDIN_FILENO);
    // if (eof[0] == '\"')
    //     eof = mini_ft_strtrim(heap,eof,"\"");
    // else if (eof[0] == '\'')
    //     eof = mini_ft_strtrim(heap,eof,"\'");
    eof = _quote(heap, eof);
    while (g_signal != SIGINT)
    {
        ++i;
        line = readline("> ");
        if (g_signal == SIGINT)
        {
            dup2(_stdin, 0);
            _close(_stdin);
            free(line);
            break;
        }
        else if (!line)
        {
            ft_printf_fd(STDERR_FILENO,"minicoquillage: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",i,eof);
            free(line);
            break;
        }
        if (strncmp(eof,line,_max_len(ft_strlen(eof),ft_strlen(line)))==EXIT_SUCCESS)
        {
            free(line);
            break;
        }
        if (*fd) 
        {
            mini_write(heap, *fd, line, ft_strlen(line));
            mini_write(heap, *fd, "\n", 1);
        }
        free(line);
    }
    _close(_stdin);
}

void    run_heredoc(t_heap * heap, t_atom * atom)
{
    int i;

    i = -1;
    while (atom->heredoc_eof[++i])
    {
        if (g_signal == SIGINT)
            break;
        if (atom->heredoc && atom->heredoc_eof[i+1] == NULL)
            open_heredoc(heap, atom);
        listen_heredoc(heap,&atom->in_fd,atom->heredoc_eof[i]);
    }
}

void	heredoc(t_heap * heap,t_ast_node * first_node)
{ 
    t_ast_node * left;
    t_parser_node * p_node;
	char				*type[13];

	build_tree_type(type);
	while (first_node && first_node->left)
	{
        if (g_signal == SIGINT)
            break;
        left = first_node->left;
        p_node = left->data;
        if (is_op(p_node->ops))
            heredoc(heap,left);
        else 
            run_heredoc(heap,p_node->atom);
        p_node = first_node->data;
        if(p_node->ops)
        {
            if (p_node->atom)
                run_heredoc(heap,p_node->atom);
        }
        first_node = first_node->right;
	}
}

void	clean_heredoc(t_heap * heap,t_ast_node * first_node)
{ 
    t_ast_node * left;
    t_parser_node * p_node;
	char				*type[13];

	build_tree_type(type);
	while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = left->data;
        if (is_op(p_node->ops))
            clean_heredoc(heap,left);
        else if (p_node->atom->heredoc) 
        {
            if (p_node->atom->in_fd)
                _close(p_node->atom->in_fd);
            if (p_node->atom->file_heredoc)
                unlink(p_node->atom->file_heredoc);
        }
        p_node = first_node->data;
        if(p_node->ops)
        {
            if (p_node->atom && p_node->atom->heredoc)
            {
                if (p_node->atom->in_fd)
                    _close(p_node->atom->in_fd);
                if (p_node->atom->file_heredoc)
                    unlink(p_node->atom->file_heredoc);
            }
        }
        first_node = first_node->right;
	}
}
