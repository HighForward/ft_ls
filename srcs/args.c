#include "../includes/ft_ls.h"

void perform_h()
{
    printf("Usage: ls [OPTION]... [FILE]...\n");
    printf("List information about the FILEs (the current directory by default).\n\n");
    printf("Options:\n");

    printf("\t-h                         Read this help and exit\n");
    printf("\t-l                         use a long listing format\n");
    printf("\t-a, --all                  do not ignore entries starting with .\n");
    printf("\t-r, --reverse              reverse order while sorting\n");
    printf("\t-t                         sort by modification time, newest first\n");
    printf("\t-G,                        in a long listing, don't print group names\n");
    printf("\t-s,                        print the allocated size of each file, in blocks\n");
    printf("\t-S                         sort by file size, largest first\n");
    exit(EXIT_SUCCESS);
}

int exit_invalid_option(char c) {
    printf("ls: invalid option -- '%c'\n", c);
    printf("Try 'ls --help' for more information.\n");
    exit(2);
}

int handle_group_args(char *args, ls_options *options) {

    const char *str = "lrRtsaGS";

    int i = 0;

    if (args && args[i] == '-' && ft_strlen(args) > 1) {
        i++;
    } else {
        return (0);
    }

    while (args[i]) {

        if (ft_strrchr(str, args[i]) != NULL) {
            if (args[i] == 'a') options->all = 1;
            if (args[i] == 'l') options->long_list = 1;
            if (args[i] == 'R') options->recursive = 1;
            if (args[i] == 'r') options->rev = 1;
            if (args[i] == 's') options->blocks_size = 1;
            if (args[i] == 't') options->sort_by_updated_time = 1;
            if (args[i] == 'G') options->not_print_group = 1;
            if (args[i] == 'S') options->sort_file_size = 1;
        } else {
            exit_invalid_option(args[i]);
        }
        i++;
    }

    return (1);

}

int getDoubleArrayLen(char **arr) {

    int i = 0;

    if (!arr)
        return (0);

    while (arr[i]) {
        i++;
    }
    return (i);
}

void push_new_arg(ls_options *options, char *arg) {

    int i = 0;
    int curr_arr_len = getDoubleArrayLen(options->paths);

    char **tmp = (char**) malloc(sizeof (char*) * (curr_arr_len + 2));
    while (i < curr_arr_len) {
        tmp[i] = options->paths[i];
        i++;
    }
    tmp[i++] = arg;
    tmp[i] = NULL;

    free(options->paths);
    options->paths = tmp;
}

int parse_args(int argc, char **argv, ls_options *options)
{
    int i = 0;
    char *arg = NULL;
    while (argv[i])
    {
        arg = argv[i];

        if (ft_strcmp(arg, "--help") == 0)
            perform_h();
        else if (ft_strcmp(arg, "-a") == 0)
            options->all = 1;
        else if (ft_strcmp(arg, "-l") == 0)
            options->long_list = 1;
        else if (ft_strcmp(arg, "-R") == 0)
            options->recursive = 1;
        else if (ft_strcmp(arg, "-r") == 0)
            options->rev = 1;
        else if (ft_strcmp(arg, "-t") == 0)
            options->sort_by_updated_time = 1;
        else if (ft_strcmp(arg, "-s") == 0)
            options->blocks_size = 1;
        else if (ft_strcmp(arg, "-G") == 0)
            options->not_print_group = 1;
        else if (ft_strcmp(arg, "-S") == 0)
            options->sort_file_size = 1;
        else if (arg[0] == '-')
            handle_group_args(arg, options);
        else
            push_new_arg(options, arg);
        i++;
    }

    return (EXIT_SUCCESS);
}