#include "../Minicoquillage.h"
char * expand(char * line, size_t index, size_t j)
{
    char * expanded;
    expanded = malloc(sizeof(char)*(j - index + 1));
    ft_strlcpy(expanded, line + index + 1, j - index);
    // printf("%s\n",expanded);
    return (expanded);
}

size_t add_token(char * line, size_t i, size_t j, t_double_link_list * list)
{
    char * temp;
    t_double_link_node * node;

    node = malloc(sizeof(*node));
    temp = malloc(sizeof(char)*(j-i + 1));
    ft_strlcpy(temp, line + i, j-i +3);
    node->data = temp;
    list->pf_insert_end(list, node);
    // printf("%s\n",temp);
    return (j);
}

size_t expand_single_quote(char * line, size_t i, size_t j, t_double_link_list * list)
{
    size_t index;
    char * temp;
    char * expanded;
    char * to_token;
    t_double_link_node * node;
    
    index = i;
    node = malloc(sizeof(*node));
    while (line[index] != '\'' && line[index])
        ++index;
    temp = malloc(sizeof(char)*(index+1));
    expanded = expand(line , index, j);
    ft_strlcpy(temp,line,index+1);
    to_token = ft_strjoin(temp,expanded);
    node->data = to_token;
    list->pf_insert_end(list, node);
    // printf("%s\n",to_token);
    return (free(temp), free(expanded),j);
}


size_t expand_double_quote(char * line, size_t i, size_t j, t_double_link_list * list)
{
    size_t index;
    char * temp;
    char * expanded;
    char * to_token;
    t_double_link_node * node;
    
    index = i;
    node = malloc(sizeof(*node));
    while (line[index] != '"' && line[index])
        ++index;
    temp = malloc(sizeof(char)*(index+1));
    expanded = expand(line , index, j);
    ft_strlcpy(temp,line,index+1);
    to_token = ft_strjoin(temp,expanded);
    node->data = to_token;
    list->pf_insert_end(list, node);
    // printf("%s\n",to_token);
    return (free(temp), free(expanded),j);
}

t_double_link_list * create_tokens(char * line)
{
    t_double_link_list * list;
    int double_quote_open;
    int word;
    int single_quote_open;
    size_t i;
    size_t j;

    double_quote_open = 0;
    word = 0;
    single_quote_open = 0;
    list = malloc(sizeof(*list));
    i = 0;
    j = 0;
    init_list(list);
    while (line[j])
    {
        if (line[j] == '"' && !double_quote_open && !single_quote_open)
            double_quote_open = 1;
        else if (line[j] == '\'' && !single_quote_open && !double_quote_open)
            single_quote_open = 1;
        else if (line[j] == '"' && double_quote_open)
        {
            double_quote_open = 0;
            i = expand_double_quote(line ,i ,j, list);
            j = i;
        }
        else if (line[j] == '\'' && single_quote_open)
        {
            single_quote_open = 0;
            i = expand_single_quote(line, i, j, list);
            j = i;
        }
        else if ((line[j] == ' '/*  || line[j] == '\n' */) && !double_quote_open && !single_quote_open && !word)
        {
            word = 1;
            i = j+1;
        }
        else if ((!line[j+1] || line[j + 1] == ' '/*  || line[j] == '\n' */) && !double_quote_open && !single_quote_open && word)
        {
            word = 0;
            i = add_token(line, i, j, list);
            j = i;
        }
        ++j;
    }

    return (list);
}
