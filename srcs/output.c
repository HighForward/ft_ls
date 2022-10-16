#include "../includes/ft_ls.h"

void print_simple(ls_node *nodes, ls_options *options) {
    ls_node *it = nodes;

    while (it) {

        if (!options->all && ft_strlen(it->content->name) && it->content->name[0] == '.') {
            it = it->next;
            continue;
        }

        ft_putstr(it->content->name);
        it = it->next;
        if (it != NULL)
            ft_putstr("  ");

    }

    if (nodes) {
        putchar('\n');
    }
}


void print_ls(ls_node *dir_nodes, char *path, ls_options *options) {

    if (options->recursive || getDoubleArrayLen(options->paths) > 1) {
        printf("%s:\n", path);
    }

    if (options->long_list)
        print_listing(dir_nodes, options);
    else
        print_simple(dir_nodes, options);

}
