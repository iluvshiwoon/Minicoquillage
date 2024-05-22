char * build_prompt() 
{
    char buffer[200] = {};
    char * prompt;
    char * temp;

    if(!getcwd(buffer, 200))
        return (NULL);
    prompt = last_ocur(buffer, '/');
    prompt = ft_strjoin("\033[1;34m", prompt+1);
    temp = ft_strjoin(prompt, "\033[0m");
    free(prompt);
    prompt = ft_strjoin(temp, (char *) { " via 🐚 \033[1;34m(Minicoquillage)\n🦪 → \033[0m" });
    free(temp);
    return (prompt);
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
