#include "../Minicoquillage.h"

size_t skip_space(char * line, size_t index)
{
    if (!line[index])
        return(index);
    while (ft_isspace(line[index+1]))
        ++index;
    return (index);
}

void add_token(size_t i, size_t j, char * line, t_double_link_list * list)
{
    t_double_link_node * node;
    char * temp;

    node = malloc(sizeof(*node));
    temp = malloc(sizeof(char)*(j-i+1));
    ft_strlcpy(temp, line + i, j-i+1);
    node->data = temp;
    list->pf_insert_end(list, node);
}

char * expand_double(size_t j, char * token)
{
    char * temp;
    char * temp2;
    char * temp3;
    size_t index;

    index = j-1;
    while(token[index] != '"')
        --index;
    temp = malloc(sizeof(char)*(j - index));
    temp3 = malloc(sizeof(char)*(index + 1));
    ft_strlcpy(temp3, token,index +1);
    ft_strlcpy(temp, token + index + 1, j - index);
    temp2 = ft_strjoin(temp3,temp);
    free(temp3);
    free(temp);
    temp = ft_strjoin(temp2, token + j + 1);
    free(temp2);
    // printf("%s\n",temp);
    return (temp);
}

char * expand_single(size_t j, char * token)
{
    char * temp;
    char * temp2;
    char * temp3;
    size_t index;

    index = j-1;
    while(token[index] != '\'')
        --index;
    temp = malloc(sizeof(char)*(j - index));
    temp3 = malloc(sizeof(char)*(index + 1));
    ft_strlcpy(temp3, token,index +1);
    ft_strlcpy(temp, token + index + 1, j - index);
    temp2 = ft_strjoin(temp3,temp);
    free(temp3);
    free(temp);
    temp = ft_strjoin(temp2, token + j + 1);
    free(temp2);
    // printf("%s\n",temp);
    return (temp);
}

void expand_tokens(t_double_link_node * node)
{
    int double_quote_open;
    char * token;
    char * temp;
    int single_quote_open;
    size_t j;

    double_quote_open = 0;
    single_quote_open = 0;
    token = node->data;
    j = 0;
    while (token[j])
    {
        if (token[j] == '"' && !single_quote_open && !double_quote_open)
            double_quote_open = 1;
        else if (token[j] == '\'' && !single_quote_open && !double_quote_open)
            single_quote_open = 1;
        else if (token[j] == '"' && double_quote_open)
        {
            double_quote_open = 0;
            temp = expand_double(j,token);
            free(token);
            node->data = temp;
            token = node->data;
            j -= 2;
        }
        else if (token[j] == '\'' && single_quote_open)
        {
            single_quote_open = 0;
            temp = expand_single(j,token);
            free(token);
            node->data = temp;
            token = node->data;
            j -= 2;
        }
        ++j;
    }

}

t_double_link_list * create_tokens(char * line)
{
    t_double_link_list * list;
    int double_quote_open;
    int single_quote_open;
    size_t i;
    size_t j;

    double_quote_open = 0;
    single_quote_open = 0;
    list = malloc(sizeof(*list));
    j = skip_space(line, j);
    i = j;
    init_list(list);
    while (line[j])
    {
        if (line[j] == '"' && !single_quote_open && !double_quote_open)
            double_quote_open = 1;
        else if (line[j] == '\'' && !single_quote_open && !double_quote_open)
            single_quote_open = 1;
        else if (line[j] == '"' && double_quote_open)
            double_quote_open = 0;
        else if (line[j] == '\'' && single_quote_open)
            single_quote_open = 0;
        else if (ft_isspace(line[j]) && !single_quote_open && !double_quote_open)
        {
            add_token(i,j,line,list);
            j = skip_space(line, j);
            i = j+1;
        }
        ++j;
    }
    add_token(i, j, line, list);
    t_double_link_node * node = list->first_node;
    while (node)
    {
        expand_tokens(node);
        node = node->next;
    }
    return (list);
}
