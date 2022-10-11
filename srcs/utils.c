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


char *ft_strcat(char *dst, char *to_cat) {

    int i = 0;
    int start_len = ft_strlen(dst);

    while (dst && to_cat && to_cat[i]) {
        dst[start_len + i] = to_cat[i];
        i++;
    }
    dst[start_len + i] = '\0';
    return dst;
}
