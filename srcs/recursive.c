#include "../includes/ft_ls.h"

void load_subdir(ls_node *dir_nodes) {

    ls_node *it = dir_nodes;

    while (it) {

        if (it->content->type == DT_DIR && it->content->name[0] != '.') {
            DIR *dp = opendir(it->content->name);
        }

        it = it->next;

    }

}

void handle_recursive(ls_options *options) {

    DIR *dp = opendir(options->base_path);

    if (dp == NULL) {
        printf("unhandled dir error\n");
        exit(EXIT_FAILURE);
    } //todo: handle errors

    ls_node *dir_nodes = process_dir(dp, ".");


    simple_print(dir_nodes);

    free_nodes(dir_nodes);
    free(dp);
}