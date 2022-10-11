#include "../includes/ft_ls.h"

void get_ls_time_format(ls_content *content, time_t time) {
    char *str_time = NULL;

    str_time = ctime(&time);
    char **split_date = ft_split(str_time, ' ');

    ft_strcat(content->time, split_date[1]);
    ft_strcat(content->time, ft_strlen(split_date[2]) == 1 ? "  " : " ");
    ft_strcat(content->time, split_date[2]);
    ft_strcat(content->time, " ");
    ft_strncat(content->time, split_date[3], 5);

    free_split(split_date);
}

void print_ls_perm_format(ls_content *content) {

    if (content->type == DT_DIR) { putchar('d'); }
    else if (content->type == DT_BLK) { putchar('b'); }
    else if (content->type == DT_CHR) { putchar('c'); }
    else if (content->type == DT_LNK) { putchar('l'); }
    else if (content->type == DT_FIFO) { putchar('p'); }
    else if (content->type == DT_SOCK) { putchar('s'); }
    else { putchar('-'); }

    printf( (content->perm & S_IRUSR) ? "r" : "-");
    printf( (content->perm & S_IWUSR) ? "w" : "-");
    printf( (content->perm & S_IXUSR) ? "x" : "-");
    printf( (content->perm & S_IRGRP) ? "r" : "-");
    printf( (content->perm & S_IWGRP) ? "w" : "-");
    printf( (content->perm & S_IXGRP) ? "x" : "-");
    printf( (content->perm & S_IROTH) ? "r" : "-");
    printf( (content->perm & S_IWOTH) ? "w" : "-");
    printf( (content->perm & S_IXOTH) ? "x" : "-");

}

//http://manpagesfr.free.fr/man/man2/stat.2.html <- stat example
//https://www.mkssoftware.com/docs/man1/ls.1.asp <- long listing infos

int get_number_len(int nb) {

    int i = 1;
    while (nb > 10) {
        nb = nb / 10;
        i++;
    }
    return (i);
}

struct ls_padding {
    int link_size;
    int u_name_size;
    int g_name_size;
    int octet_size;
    int time_size;
};

struct ls_padding handle_listing_padding(struct ls_node *dir_nodes) {
    ls_node *it = dir_nodes;

    struct ls_padding paddings;
    ft_bzero(&paddings, sizeof(struct ls_padding));

    while (it) {

        int tmp_link_size = get_number_len(it->content->nb_link);
        if (paddings.link_size < tmp_link_size)
            paddings.link_size = tmp_link_size;

        if (paddings.u_name_size < ft_strlen(it->content->u_name))
            paddings.u_name_size = ft_strlen(it->content->u_name);

        if (paddings.g_name_size < ft_strlen(it->content->g_name))
            paddings.g_name_size = ft_strlen(it->content->g_name);

        int tmp_octets_size = get_number_len((int)it->content->octets);
        if (paddings.octet_size < tmp_octets_size)
            paddings.octet_size = tmp_octets_size;

        if (paddings.time_size < ft_strlen(it->content->time))
            paddings.time_size = ft_strlen(it->content->time);

        it = it->next;
    }
    return paddings;
}


void print_listing(ls_node *nodes) {

    ls_node *it = nodes;
    long block_size = it ? it->content->blksize : 0;

    printf("total %ld\n", block_size);

    struct ls_padding paddings = handle_listing_padding(nodes);
    while (it)
    {
        print_ls_perm_format(it->content);
        printf(" %*d %*s %*s %*lld %*s %s",
               paddings.link_size, it->content->nb_link,
               paddings.u_name_size, it->content->u_name,
               paddings.g_name_size, it->content->g_name,
               paddings.octet_size, it->content->octets,
               paddings.time_size, it->content->time,
               it->content->name);

        if (ft_strlen(it->content->sym_link) > 0) {
            printf(" -> %s", it->content->sym_link);
        }

        putchar('\n');

        it = it->next;
    }

}
