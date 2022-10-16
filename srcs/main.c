#include "../includes/ft_ls.h"

//1427295

int process_ls(char *path, ls_options *options) {

    DIR *dp = opendir(path);
    ls_node *dir_nodes = NULL;

    if (dp == NULL) {


        //todo: handle errno here

        if (errno == EACCES || errno == EBADF || errno == EMFILE || errno == ENOENT || errno == ENOMEM || errno == ENOTDIR) {
            fprintf(stderr, "ls: cannot open directory '%s': %s\n", path, strerror(errno));
            return (EXIT_SUCCESS);
        }

        ls_content *content = alloc_content_struct();
        load_data_and_insert_node(&dir_nodes, content, path, options);
        content->name = ft_strdup(path);

    } else {
        if (has_next_item(options) && ft_strcmp(path, options->base_path) != 0) {
            ft_putstr("\n");
        }
        dir_nodes = process_dir(dp, path, options);
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

int main(int argc, char **argv)
{
    ls_options options;
    ft_bzero(&options, sizeof(options));

    if (parse_args(argc, argv + 1, &options))
        return (EXIT_FAILURE);

    int i = double_array_len(options.paths);
    int curr_index = i;
    options.base_path = ".";
    do
    {
        if (i > 0) {
            options.base_path = options.paths[curr_index - 1];
        }

        if (process_ls(options.base_path, &options))
            return (EXIT_FAILURE);

        curr_index--;

        if (curr_index > 0)
            printf("\n");

    } while (curr_index > 0);

    free(options.paths);

    return (1);
}