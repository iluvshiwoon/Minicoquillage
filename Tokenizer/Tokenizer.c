#include "../Minicoquillage.h"

int check_syntax(char * line)
{
    static size_t single_quote;
    static size_t double_quote;

    while(*line)
    {
        if (*line == '\'')
            single_quote++;
        else if (*line == '\"')
            double_quote++;
        line++;
    }
    return (single_quote % 2 == 0 && double_quote % 2 == 0);
}

char * concat_input(t_double_link_list * list)
{
    t_double_link_node * node;
    t_double_link_node * temp_node;
    size_t i;
    char * dst;
    char * temp;
    size_t l1;
    size_t l2;

    node = list->first_node;
    i = 0;
    while (node)
    {
        node = node->next;
        i++;
    }
    node = list->first_node;


    if (i == 1)
        dst = node->data;
    else if (i >= 2)
    {
        dst = ft_strjoin((char *)node->data, (char *)node->next->data);
        i--;
        node = node->next->next;
    }
    while (i != 1)
    {
        temp = ft_strjoin(dst,(char *)node->data);
        free(dst);
        dst = temp;
        node = node->next;
        i--;
    }
    return (dst);
}

char * get_line()
{
    char * prompt; 
    char * line;
    t_double_link_list * list;
    t_double_link_node * node;
    char * final;
    
    list = malloc(sizeof(*list));
    init_list(list);
    node = malloc(sizeof(*node));
    prompt = build_prompt();
    line = readline(prompt);
    node->data = line;
    list->pf_insert_end(list, node);
    while (!check_syntax(line))
    {
        node = malloc(sizeof(*node));
        line = readline("· ");
        node->data = line;
        list->pf_insert_end(list, node);
    }    
    final = concat_input(list); 
    if (final && *final)
       add_history(final);
    if (!list->first_node->next)
        final = ft_strdup(final);
    dl_free_list(list);
    return (free(prompt),final);
}

t_double_link_list ** tokenizer(void)
{
    char ** multiline;
    char * line;

    // line = "echo 'hello' ; echo 'world' ; ff ; bot diff; aaargh";
    
    line = get_line();
    multiline = ft_mysplit(line, "\n;");
    free(line);
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
