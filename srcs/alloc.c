#include "../includes/ft_ls.h"

ls_node	*ls_lstnew(void *content)
{
    ls_node *new;

    if (!(new = (ls_node*)malloc(sizeof(ls_node))))
        return (NULL);
    ft_bzero(new, sizeof(struct ls_node));
    new->content = content;
    new->next = NULL;
    return (new);
}

ls_content *alloc_content_struct() {

    ls_content *content = NULL;

    if (!(content = malloc(sizeof(struct ls_content)))) {
        return (NULL);
    }

    ft_bzero(content, sizeof(struct ls_content));

    return (content);
}
