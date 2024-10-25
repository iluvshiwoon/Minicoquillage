/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:32:45 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/25 19:30:30 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

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
    if (access("/tmp",F_OK) == EXIT_FAILURE)
        error_exit("/tmp directory doesn't exist!\n", heap->heap_allocated);
    else if (access("/tmp",R_OK | W_OK) == EXIT_FAILURE)
        error_exit("Wrong permission for /tmp directory\n", heap->heap_allocated);
    nb = ft_itoa(i++);
    tmp = mini_ft_strjoin(heap->heap_allocated,heap->list,tmp,nb);
    free(nb);
    atom->heredoc_fd = open(tmp, O_RDWR | O_EXCL | O_CREAT , S_IRUSR | S_IWUSR);
    if (atom->heredoc_fd == -1)
        return(perror(NULL),error_exit("open failed\n", heap->heap_allocated));
    atom->file_heredoc = tmp;
}

void    listen_heredoc(t_heap * heap, int * fd, char * eof)
{
    char * line;
    while (1)
    {
        line = readline("> ");
        if (strncmp(eof,line,ft_strlen(eof))==EXIT_SUCCESS)
            break;
        if (*fd) 
        {
            mini_write(heap, *fd, line, ft_strlen(line));
            mini_write(heap, *fd, "\n", 1);
        }
    }
}

void    run_heredoc(t_heap * heap, t_atom * atom)
{
    int i;

    i = -1;
    while (atom->heredoc_eof[++i])
    {
        if (atom->heredoc && atom->heredoc_eof[i+1] == NULL)
            open_heredoc(heap, atom);
        listen_heredoc(heap,&atom->heredoc_fd,atom->heredoc_eof[i]);
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
            close(p_node->atom->heredoc_fd);
            unlink(p_node->atom->file_heredoc);
        }
        p_node = first_node->data;
        if(p_node->ops)
        {
            if (p_node->atom && p_node->atom->heredoc)
            {
                close(p_node->atom->heredoc_fd);
                unlink(p_node->atom->file_heredoc);
            }
        }
        first_node = first_node->right;
	}
}
