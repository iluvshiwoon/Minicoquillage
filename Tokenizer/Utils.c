#include "../Minicoquillage.h"

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

void print_list(t_double_link_list * tokens_lists)
{
    size_t i;
    t_double_link_node * node;

    i = 0;
    node = tokens_lists->first_node;
    while(node)
    {
        printf("%s\n", (char*)node->data);
        node = node->next;
    }
}
