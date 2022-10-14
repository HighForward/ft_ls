#include "../includes/ft_ls.h"

int process_ls(char *path, ls_options *options) {

    DIR *dp = opendir(path);

    //todo: handle errors
    if (dp == NULL) {
        printf("ft_ls: cannot open directory '%s': Permission denied\n", path);
        return (EXIT_SUCCESS);
    }

    ls_node *dir_nodes = process_dir(dp, path, options);

    print_ls(dir_nodes, path, options);

    if (dir_nodes) {

        ls_node *iterator = dir_nodes;

        while (options->recursive && iterator != NULL) {

            if (iterator->content->type == DT_DIR && dir_is_not_dot(iterator->content->name) == 0) {

                char *tmp_str = get_dir_path(path, iterator->content->name);

                if (options->recursive) {
                    ft_putstr("\n");
                }

                if (process_ls(tmp_str, options))
                    return (EXIT_SUCCESS);

                free(tmp_str);
            }
            iterator = iterator->next;
        }
        free_nodes(dir_nodes);
        free(dp);
    }

    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    ls_options options;
    ft_bzero(&options, sizeof(options));

    if (parse_args(argc, argv + 1, &options))
        return (EXIT_FAILURE);

    if (process_ls(options.base_path, &options))
        return (EXIT_FAILURE);

    return (1);
}