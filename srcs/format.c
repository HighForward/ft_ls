#include "../includes/ft_ls.h"

void get_ls_time_format(ls_content *content, time_t time) {
    char *str_time = NULL;

    str_time = ctime(&time);
    char **split_date = ft_split(str_time, ' ');

    ft_strcat(content->time, split_date[1]);
    ft_strcat(content->time, " ");
    ft_strcat(content->time, split_date[2]);
    ft_strcat(content->time, " ");
    ft_strncat(content->time, split_date[3], 5);

    free_split(split_date);
}

//http://manpagesfr.free.fr/man/man2/stat.2.html <- stat example
//https://www.mkssoftware.com/docs/man1/ls.1.asp <- long listing infos

void handle_listing_padding(struct ls_node *dir_nodes, char *path, ls_options *options) {
//    ls_node *it = dir_nodes;
//
//    int link_size = 0;
//    int u_name_size = 0;
//    int g_name_size = 0;
//    int octet_size = 0;
//
//    while (it) {
//
//        if (link_size < it->content->nb_link)
//            link_size = it->content->nb_link;
//
//        if (u_name_size < ft_strlen(it->content->u_name))
//            u_name_size = ft_strlen(it->content->u_name);
//
//        if (g_name_size < ft_strlen(it->content->g_name))
//            g_name_size = ft_strlen(it->content->g_name);
//
//        const char *octet_str = ft_itoa((int)it->content->octets);
//
//        if (octet_size < ft_strlen(octet_str))
//            octet_size = ft_strlen(octet_str);
//
//        free((void*)octet_str);
//
//        it = it->next;
//    }
//
}


void print_listing(ls_node *nodes) {

    ls_node *it = nodes;

    while (it)
    {
        printf("%s %d %s %s %lld %s %s\n",
               "-rwxrwxrwx",
               it->content->nb_link,
               it->content->u_name,
               it->content->g_name,
//               octet_size,
               it->content->octets,
               it->content->time,
               it->content->name);

        it = it->next;
    }

}
