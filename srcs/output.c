#include "../includes/ft_ls.h"

void print_debug(ls_content *content) {
    printf("type: %d\nname: %s\n", content->type, content->name);
//    if (content->type == DT_DIR)
}

void simple_print(ls_node *dir_nodes) {

    ls_node *it = dir_nodes;
    while (it)
    {
        ls_content *content = it->content;
        ft_putstr(content->name);
        if (it->next != NULL)
            ft_putstr("  ");
//        print_debug(content);
//        print_long_listing(it->content);
        it = it->next;
    }
}
