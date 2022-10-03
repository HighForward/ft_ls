#include "../includes/ft_ls.h"

int process_ls(ls_options *options) {

    DIR *dp = opendir(options->base_path);
    if (dp == NULL) {
        printf("unhandled dir error\n");
        exit(EXIT_FAILURE);
    } //todo: handle errors

    ls_node *dir_nodes = process_dir(dp, ".");

    simple_print(dir_nodes);

    free_nodes(dir_nodes);
    free(dp);

    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    ls_options options;
    ft_bzero(&options, sizeof(options));

    if (parse_args(argc, argv + 1, &options))
        return (EXIT_FAILURE);

//    if (options.recursive)
//        handle_recursive(&options);

    if (process_ls(&options))
        return (EXIT_FAILURE);

    return (1);
}