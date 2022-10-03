#include "../includes/ft_ls.h"

ls_node	*ls_lstnew(void *content)
{
    ls_node *new;

    if (!(new = (ls_node*)malloc(sizeof(ls_node))))
        return (NULL);
    new->content = content;
    new->next = NULL;
    new->subdir = NULL;
    return (new);
}
