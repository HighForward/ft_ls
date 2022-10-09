#include "../includes/ft_ls.h"

void print_simple(ls_node *node) {
    if (node) {
        ft_putstr(node->content->name);
        if (node->next != NULL)
            ft_putstr("  ");
    }
}

void get_ls_time_format(char (*tmp_time)[100], time_t *time) {
    char *str_time = ctime(time);
    char **split_date = ft_split(str_time, ' ');

    ft_strcat(*tmp_time, split_date[1]);
    ft_strcat(*tmp_time, " ");
    ft_strcat(*tmp_time, split_date[2]);
    ft_strcat(*tmp_time, " ");
    ft_strncat(*tmp_time, split_date[3], 5);
}

//http://manpagesfr.free.fr/man/man2/stat.2.html <- stat example
//https://www.mkssoftware.com/docs/man1/ls.1.asp <- long listing infos
void print_listing(ls_node *node, char *path) {

    if (node) {
        struct stat sb;

        const char *dir_path = get_dir_path(path, node->content->name);

        if (stat(dir_path, &sb) < 0) {
            str_error("error stat");
        }


        char *perm = "-rw-rw-rw-";
        int nb_link = 1;
        char *u_name = getpwuid(sb.st_uid)->pw_name;
        char *g_name = getgrgid(sb.st_gid)->gr_name;
        long long file_size = sb.st_size;

        char tmp_time[100];
        ft_bzero(tmp_time, 100);
        get_ls_time_format(&tmp_time, &sb.st_ctime);

        printf("%s %d %s %s %lld %s %s\n", perm, nb_link, u_name, g_name, file_size, tmp_time, node->content->name);
    }
}

void print_ls(ls_node *dir_nodes, char *path, ls_options *options) {

    if (options->recursive) {
        printf("%s:\n", path);
    }

    ls_node *it = dir_nodes;

    while (it)
    {
        if (options->long_list) {
            print_listing(it, path);
        } else {
            print_simple(it);
        }
        it = it->next;
    }

    if (!options->long_list)
        putchar('\n');

    if (options->recursive)
        putchar('\n');
}
