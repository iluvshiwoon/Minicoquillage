#include "../Minicoquillage.h"

int ft_isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
            c == '\f' || c == '\r');
}

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
    return (list);
}
