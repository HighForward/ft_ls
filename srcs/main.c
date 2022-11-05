#include "../includes/ft_ls.h"

int open_path(DIR *dp, char *path, ls_node **dir_nodes, ls_options *options) {

    if (dp == NULL)
    {
        if (errno == EACCES || errno == EBADF || errno == EMFILE || errno == ENOMEM)
        {
            fprintf(stderr, "ls: cannot open directory '%s': %s\n", path, strerror(errno));
            return (EXIT_FAILURE);
        }
        else if (errno == ENOTDIR || errno == ENOENT)
        {
            options->not_print_total = 1;
            ls_content *content = alloc_content_struct();
            content->name = ft_strdup(path);
            load_data_and_insert_node(dir_nodes, content, path, options);
        }
    }
    else
    {
        if (has_next_item(options) && ft_strcmp(path, options->base_path) != 0)
            ft_putstr("\n");

        process_dir(dp, path, dir_nodes, options);
    }
    return (EXIT_SUCCESS);
}

int process_ls(char *path, ls_options *options) {

    DIR *dp = opendir(path);
    ls_node *dir_nodes = NULL;

    if (open_path(dp, path, &dir_nodes, options)) {
        return (EXIT_SUCCESS);
    }

    print_ls(dir_nodes, path, options);

    if (dir_nodes) {

        ls_node *iterator = dir_nodes;

        while (options->recursive && iterator != NULL) {

            if (iterator->content->type == DT_DIR && dir_is_not_dot(iterator->content->name) == 0) {

                char *tmp_str = get_dir_path(path, iterator->content->name);

                if (process_ls(tmp_str, options))
                    return (EXIT_SUCCESS);

                free(tmp_str);
            }
            iterator = iterator->next;
        }
    }


    free_nodes(dir_nodes);
    if (dp != NULL)
        closedir(dp);

    return (EXIT_SUCCESS);
}

int exec_paths(ls_options *options) {
    int i = double_array_len(options->paths);
    int curr_index = i;
    options->base_path = ".";
    do
    {
        if (i > 0) {
            options->base_path = options->paths[curr_index - 1];
        }

        if (process_ls(options->base_path, options))
            return (EXIT_FAILURE);

        curr_index--;

        if (curr_index > 0)
            printf("\n");

    } while (curr_index > 0);
}

int main(int argc, char **argv)
{
    ls_options options;
    ft_bzero(&options, sizeof(options));

    if (parse_args(argc, argv + 1, &options))
        return (EXIT_FAILURE);

    if (exec_paths(&options)) {
        return (EXIT_FAILURE);
    }

    free_ptr(options.paths);

    return (1);
}