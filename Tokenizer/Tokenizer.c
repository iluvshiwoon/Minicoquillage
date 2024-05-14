#include "../Minicoquillage.h"
static int free_all(char ** multiline)
{
    size_t i;

    i = 0;
    while(multiline[i])
        free(multiline[i++]);
    free(multiline);
    return (0);
}

t_double_link_list ** tokenizer(void)
{
    char * line;
    size_t i;
    size_t j;
    char ** multiline;
    char *** cmds; 
    t_double_link_list ** cmd_list;
    t_double_link_node * node;

    // line = readline("Minicoquillage$ ");
    line = "echo 'hello' ; echo 'world'";
    // if (line && *line)
    //     add_history(line);
    multiline = ft_mysplit(line, "\n;");
    i = 0;
    while (multiline[i])
    {
        // printf("%s\n",multiline[i]);
        i++;
    }
    cmd_list = malloc(sizeof(*cmd_list)*(i+1));
    cmd_list[i] = NULL;
    cmds = malloc(sizeof(*cmds)*(i+1));
    cmds[i] = NULL;
    if (!cmd_list || !cmds)
        return (free_all(multiline), free(line), NULL);
    i = 0;
    while (multiline[i])
    {
        cmd_list[i] = malloc(sizeof(*cmd_list[i]));
        cmds[i] = ft_mysplit(multiline[i], " ");
        init_list(cmd_list[i]);
        // printf("%s\n",multiline[i]);
        i++;
    }
    i = 0;
    while (cmds[i])
    {
        j = 0;
        while(cmds[i][j])
        {
            node = malloc(sizeof(*node));
            node->data = cmds[i][j];
            cmd_list[i]->pf_insert_end(cmd_list[i], node);
            // printf("%s\n", cmds[i][j]);
            j++;
        }
        i++;
    }
    i = 0;
    int is_last = 0;
    while (cmd_list[i])
    {
        node = cmd_list[i]->first_node;
        while(node)
        {
            printf("%s\n", (char*)node->data);
            node = node->next;
        }
        i++;
    }

    return (free_all(multiline), free(line), cmd_list);
}
int main (void)
{
    while (1)
        tokenizer();
    return (0);
}
  
