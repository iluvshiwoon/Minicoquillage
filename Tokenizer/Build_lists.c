#include "../Minicoquillage.h"

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
