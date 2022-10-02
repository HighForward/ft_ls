#include "../includes/ft_ls.h"

void lst_add_node_sort(t_list **alst, t_list *new)
{
    t_list *curr = NULL;
    t_list *prev = NULL;
    int n = 0;

    if (alst) {

        if (*alst == NULL)
            *alst = new;
        else {

            curr = (*alst);
//            n = ft_strncmp(curr->content, new->content, ft_strlen(new->content));
            while (curr->next != NULL && (n = ft_strncmp((char*)curr->content, (char*)new->content, ft_strlen((char*)new->content))) < 0) {
                printf("inside loop: %s %s %d %d\n", (char*)curr->content, (char*)new->content, n, ft_strncmp((char*)curr->content, (char*)new->content, ft_strlen((char*)new->content)));

                curr = curr->next;
            }
            printf("break %s %s\n", (char*)curr->content, (char*)new->content);


            t_list *tmp = NULL;

            if (curr->next != NULL) {
                printf("next is not null\n");
                tmp = curr->next;
            }

            curr->next = new;
            new->next = tmp;
//            if (curr->next == NULL) {
//                printf("insert at end: %s %s %d %d\n", (char*)curr->content, (char*)new->content, n, ft_strncmp((char*)curr->content, (char*)new->content, ft_strlen((char*)new->content)));
//            }
        }
    }
}

int main(int argc, char **argv)
{
    t_list *nodes = NULL;
    DIR *dp;
    struct dirent *dirp;

    dp = opendir(".");

    while ((dirp = readdir(dp)) != NULL) {
        t_list *tmp_new = ft_lstnew(dirp->d_name);
        lst_add_node_sort(&nodes, tmp_new);
    }


    t_list *ptr_node = nodes;
    while (ptr_node) {
        print_long_listing(ptr_node->content);
        ptr_node = ptr_node->next;
    }
}