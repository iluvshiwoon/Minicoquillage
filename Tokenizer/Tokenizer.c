#include "../Minicoquillage.h"

t_double_link_list ** tokenizer(void)
{
    char * line;
    char ** multiline;
    char * prompt;

    // line = "echo 'hello' ; echo 'world' ; ff ; bot diff; aaargh";
    
    prompt = build_prompt();
    line = readline(prompt);
    if (line && *line)
        add_history(line);
    multiline = ft_mysplit(line, "\n;");
    return (free(prompt),create_tokens_lists(multiline));
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
