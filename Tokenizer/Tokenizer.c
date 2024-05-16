#include "../Minicoquillage.h"

void dl_free_list(t_double_link_list * tokens_list)
{
    t_double_link_node * node;

    node = tokens_list->first_node;
    while (node)
    {
        free(node->data);
        node = node->next;
    }
    free(tokens_list);
}

static void free_all(char ** multiline, t_double_link_list ** tokens_list, char *** tokens)
{
    size_t i;

    i = 0;
    free_split(multiline);
    while(tokens_list[i])
        dl_free_list(tokens_list[i++]);
    free(tokens_list);
    i = 0;
    if (!tokens)
        return;
    while(tokens[i])
        free_split(tokens[i]);
    free(tokens);
}

void free_previous_tokens(size_t i, char *** tokens)
{
    size_t j;

    j = 0;
    while (j < i)
        free_split(tokens[i++]);
    free(tokens);
}

t_double_link_list ** create_tokens_lists(char ** multiline)
{
    char *** tokens;
    t_double_link_list ** tokens_lists;
    t_double_link_node * node;
    size_t i;
    size_t j;

    i = 0;
    while (multiline[i])
        i++;

    tokens_lists = malloc(sizeof(tokens_lists)*(i+1));
    tokens = malloc(sizeof(tokens)*(i+1));
    if (!tokens_lists || !tokens)
        return NULL;
    tokens[i] = NULL;
    tokens_lists[i] = NULL;

    i = 0;
    while (multiline[i])
    {
        tokens_lists[i] = malloc(sizeof(*tokens_lists[i]));
        tokens[i] = ft_mysplit(multiline[i], " ");
        if (!tokens_lists[i] || tokens[i])
            return (free_previous_tokens(i,tokens),free_all(multiline, tokens_lists, NULL), NULL);
        init_list(tokens_lists[i]);
        i++;
    }

    i = 0;
    while (tokens[i])
    {
        j = 0;
        while(tokens[i][j])
        {
            node = malloc(sizeof(*node));
            if (!node)
                return (free_all(multiline, tokens_lists, tokens), NULL);
            node->data = tokens[i][j];
            tokens_lists[i]->pf_insert_end(tokens_lists[i], node);
            j++;
        }
        i++;
    }

    i = 0;
    int is_last = 0;
    while (tokens_lists[i])
    {
        node = tokens_lists[i]->first_node;
        while(node)
        {
            printf("%s\n", (char*)node->data);
            node = node->next;
        }
        i++;
    }
    return (free)
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
    cmd_list = malloc(sizeof(cmd_list)*(i+1));
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
  
