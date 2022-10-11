#include "../includes/ft_ls.h"

void print_simple(ls_node *nodes) {
    ls_node *it = nodes;
    while (it) {
        ft_putstr(it->content->name);
        it = it->next;
        if (it != NULL)
            ft_putstr("  ");
    }
}


void print_ls(ls_node *dir_nodes, char *path, ls_options *options) {

    if (options->recursive) {
        printf("%s:\n", path);
    }

    if (options->long_list)
        print_listing(dir_nodes);
    else
        print_simple(dir_nodes);


    if (!options->long_list)
        putchar('\n');

    if (options->recursive)
        putchar('\n');
}
