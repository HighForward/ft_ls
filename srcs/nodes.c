#include "../includes/ft_ls.h"

int trigger_insert(ls_content *curr, ls_content *next, ls_options *options)
{

    if (options->sort_by_updated_time) {
        return (!options->rev ?
                curr->last_update <= next->last_update : curr->last_update >= next->last_update);
    }
    if (options->sort_file_size) {
        return (!options->rev ?
                curr->octets <= next->octets : curr->octets >= next->octets);
    } else {
        return (!options->rev ?
                ft_strcmp_lower(curr->name, next->name) >= 0 : ft_strcmp_lower(curr->name, next->name) <= 0);
    }
}

void lst_add_node_sort(ls_node **alst, ls_node *new, ls_options *options)
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
                if (trigger_insert(curr->content, new->content, options))
                {
                    ls_node *tmp = curr->next;
                    curr->next = new;
                    new->next = tmp;

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