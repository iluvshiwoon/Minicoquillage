/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:48:19 by kgriset           #+#    #+#             */
/*   Updated: 2024/10/27 18:57:31 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minicoquillage.h"

void	_exec_tree(t_heap * heap,t_ast_node * first_node, char ** envp);

char ** _args(t_heap * heap, char * cmd, char ** args)
{
    char ** new_args;
    int i;
    int j;

    i = -1;
    while (args[++i]);
    new_args = wrap_malloc(heap->heap_allocated, heap->list,sizeof(*new_args) * (i + 2));
    new_args[0] = cmd;
    new_args[i+1] = NULL;
    i = -1;
    j = 0;
    while (args[++i])
        new_args[++j] = args[i];
    return(new_args);
}

void execution(t_heap_allocated * heap_allocated, t_ast * ast, char * line, char ** envp)
{
    t_heap heap;

    heap.heap_allocated = heap_allocated;
    heap.list = heap_allocated->exec;
    // print_tree(&heap,ast->first_node);
    // printf("\n");
    heredoc(&heap, ast->first_node);
    _exec_tree(&heap, ast->first_node, envp);
    add_history(line);
    clean_heredoc(&heap, ast->first_node);
}

int _exec_node(t_heap * heap, char * path, t_parser_node * p_node, char ** envp)
{
    pid_t pid;
    int wstatus;

    pid = fork();
    if (pid < 0)
        return(perror(NULL),error_exit("fork failed\n",heap->heap_allocated),4);
    if (pid == 0)
    {
        // execve(path,_args(heap,p_node->atom->cmd,p_node->atom->args),envp);
        execve(path,p_node->atom->args,envp);
        perror("execve");
    }
    waitpid(pid, &wstatus,0);
    if (WIFEXITED(wstatus))
        printf("%d\n",WEXITSTATUS(wstatus));
    return (1);
}

void	_exec_tree(t_heap * heap,t_ast_node * first_node, char ** envp)
{
    t_ast_node * left;
    t_parser_node * p_node;
    char * path;
    // static int status;

	while (first_node && first_node->left)
	{
        left = first_node->left;
        p_node = left->data;
        if (is_op(p_node->ops))
            _exec_tree(heap,left, envp);
        else 
        {
            path = get_path(heap,p_node->atom->cmd);
            if (path)
                _exec_node(heap,path,p_node,envp);
            // printf("%s ",p_node->atom->cmd);
            // print_t_options(p_node->atom);
            // print_t_args(p_node->atom);
            // if (p_node->atom->heredoc)
            // {
            //     print_t_stdin(p_node->atom);
            //     print_t_heredoc(p_node->atom);
            // }
            // else 
            // {
            //     print_t_heredoc(p_node->atom);
            //     print_t_stdin(p_node->atom);
            // }
            // print_t_stdout(p_node->atom);
        }
        p_node = first_node->data;
        // if(p_node->ops)
        // {
            // if (p_node->atom)
            // {
            //     if (p_node->atom->heredoc)
            //     {
            //         print_t_stdin(p_node->atom);
            //         print_t_heredoc(p_node->atom);
            //     }
            //     else 
            //     {
            //         print_t_heredoc(p_node->atom);
            //         print_t_stdin(p_node->atom);
            //     }
            //     print_t_stdout(p_node->atom);
            // }
            // if (p_node->ops != EOE)
            //     printf("%s ",type[p_node->ops]);
        // }
        first_node = first_node->right;
	}
}
