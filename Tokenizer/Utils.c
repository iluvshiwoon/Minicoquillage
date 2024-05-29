#include "../Minicoquillage.h"

int ft_isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
            c == '\f' || c == '\r');
}

void print_list(t_double_link_list * tokens_lists)
{
    size_t i;
    t_double_link_node * node;

    i = 0;
    node = tokens_lists->first_node;
    while(node)
    {
        printf("%s$\n", (char*)node->data);
        node = node->next;
    }
}
