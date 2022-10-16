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
    exit(EXIT_SUCCESS);
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
        else if (!options->base_path)
            options->base_path = argv[i];
        i++;
    }

    if (options->base_path == NULL)
        options->base_path = ".";

    return (EXIT_SUCCESS);
}