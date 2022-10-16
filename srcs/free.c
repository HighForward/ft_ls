#include "../includes/ft_ls.h"


void free_nodes(ls_node *nodes)
{
    ls_node *now = nodes;
    ls_node *after = NULL;

    if (now)
    {
        while (now)
        {
            if (now->next)
                after = now->next;
            else
                after = NULL;
            if (now->content) {
                if (now->content->g_name)
                    free(now->content->g_name);
                if (now->content->name)
                    free(now->content->name);
                free(now->content);
            }
            free(now);
            now = after;
        }
        nodes = NULL;
    }
}

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        if (split[i])
            free(split[i]);
        i++;
    }
    free(split);
}