#include "../includes/ft_ls.h"

ls_content *load_dir(struct dirent *dir) {

    ls_content *content = NULL;

    if (!(content = malloc(sizeof(struct ls_content)))) {
        return (NULL);
    }
    content->name = dir->d_name;
    content->type = dir->d_type;

    return (content);
}

ls_node *process_dir(DIR *dp, char *dir_path) {

    ls_node *nodes = NULL;
    ls_content *content = NULL;

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL)
    {
        if (!(content = load_dir(dirp)))
            return (NULL);

        ls_node *tmp_new = ls_lstnew(content);
        tmp_new->dir_path = dir_path;
        lst_add_node_sort(&nodes, tmp_new);
    }
    return nodes;
}

void lst_add_node_sort(ls_node **alst, ls_node *new)
{
    ls_node *curr = NULL;

    if (alst && new)
    {
        if (*alst == NULL)
            *alst = new;
        else
        {
            curr = (*alst);
            do
            {
                if (ft_strncmp(curr->content->name, new->content->name, ft_strlen(new->content->name)) > 0)
                {
                    ls_node *tmp = curr->next;
                    curr->next = new;
                    new->next = tmp;

                    // swap content
                    ls_content *test = curr->content;
                    curr->content = curr->next->content;
                    curr->next->content = test;
                    return ;
                } else if (curr->next == NULL) {
                    curr->next = new;
                    return ;
                }
                curr = curr->next;
            } while (curr != NULL) ;
        }
    }
}