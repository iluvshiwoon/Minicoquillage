#include "../Minicoquillage.h"

void dl_free_list(t_double_link_list * tokens_list)
{
    t_double_link_node * node;
    t_double_link_node * node_temp;

    node = tokens_list->first_node;
    while (node)
    {
        free(node->data);
        node_temp = node;
        node = node->next;
        free(node_temp);
    }
    free(tokens_list);
}

static void free_all(char ** multiline, t_double_link_list ** tokens_list, char *** tokens)
{
    size_t i;

    i = 0;
    if (multiline)
        free_split(multiline);
    if (tokens_list)
    {
        while(tokens_list[i])
            dl_free_list(tokens_list[i++]);
        free(tokens_list);
    }
    if (tokens)
    {
        i = 0;
        while(tokens[i])
            free(tokens[i++]);
        free(tokens);
    }
}

void free_previous_tokens(size_t i, char *** tokens)
{
    size_t j;

    j = 0;
    while (j < i)
        free_split(tokens[i++]);
    free(tokens);
}

void print_tokens_list(t_double_link_list ** tokens_lists)
{
    size_t i;
    t_double_link_node * node;

    i = 0;
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
}

t_double_link_list ** fill_tokens_lists(char ** multiline, char *** tokens, t_double_link_list ** tokens_lists)
{
    size_t i;
    size_t j;
    t_double_link_node * node;

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
    return (tokens_lists);
}

t_double_link_list ** init_tokens_lists (char ** multiline, char *** tokens, t_double_link_list ** tokens_lists)
{
    size_t i;

    i = 0;
    while (multiline[i])
    {
        tokens_lists[i] = malloc(sizeof(*tokens_lists[i]));
        tokens[i] = ft_mysplit(multiline[i], " ");
        if (!tokens_lists[i] || !tokens[i])
            return (free_previous_tokens(i,tokens),free_all(multiline, tokens_lists, NULL), NULL);
        init_list(tokens_lists[i]);
        i++;
    } 

    return (tokens_lists);
}

t_double_link_list ** create_tokens_lists(char ** multiline)
{
    char *** tokens;
    t_double_link_list ** tokens_lists;
    size_t i;

    i = 0;
    while (multiline[i])
        i++;
    tokens_lists = malloc(sizeof(tokens_lists)*(i+1));
    tokens = malloc(sizeof(tokens)*(i+1));
    if (!tokens_lists || !tokens)
        return NULL;
    tokens[i] = NULL;
    tokens_lists[i] = NULL;

    tokens_lists = init_tokens_lists(multiline, tokens, tokens_lists); 
    if (!tokens_lists)
        return NULL;
    tokens_lists = fill_tokens_lists(multiline, tokens, tokens_lists);
    if (!tokens_lists)
        return NULL;

    print_tokens_list(tokens_lists); 
    return (free_all(multiline, NULL, tokens),tokens_lists);
}

char * last_ocur (char * string , char c)
{
    size_t i;
    size_t last;

    i = 0;
    last = 0;
    while(string[i])
    {
        if (string[i] == c)
            last = i;
        i++;
    }
    if (!last)
        return NULL;
    return (string + last);
}

t_double_link_list ** tokenizer(void)
{
    char * line;
    char ** multiline;
    char prompt[200] = {};
    char * P;

    // line = "echo 'hello' ; echo 'world' ; ff ; bot diff; aaargh";
    if(!getcwd(prompt, 200))
        return (NULL);
    P = last_ocur(prompt, '/');
    P = ft_strjoin("\033[1;34m", P+1);
    P = ft_strjoin(P, "\033[0m");
    P = ft_strjoin(P, (char *) { " via 🐚 \033[1;34m(Minicoquillage)\n🦪 → \033[0m" });
    // line = readline(" via 🐚 (Minicoquillage) ");
    line = readline(P);
    if (line && *line)
        add_history(line);

    multiline = ft_mysplit(line, "\n;");
    free(P);
    return (create_tokens_lists(multiline));
}

int main (void)
{
    t_double_link_list ** tokens_lists;

    // size_t i = 2;
    // while (i--)
    // {
    //     tokens_lists = tokenizer();
    //     free_all(NULL,tokens_lists,NULL);
    // }

    while (1)
    {
        tokens_lists = tokenizer();
        free_all(NULL,tokens_lists,NULL);
    }

    return (0);
}
  
