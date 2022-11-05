#include "../includes/ft_ls.h"

void print_ls_perm_format(ls_content *content) {

    switch (content->perm & S_IFMT) {
        case S_IFBLK:  putchar('b');        break;
        case S_IFCHR:  putchar('c');        break;
        case S_IFDIR:  putchar('d');        break;
        case S_IFIFO:  putchar('p');        break;
        case S_IFLNK:  putchar('l');        break;
        case S_IFSOCK: putchar('s');        break;
        default: putchar('-');              break;
    }

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

void print_ls_time_format(ls_content *content, int time_padding) {
    char *str_time = NULL;

    str_time = ctime(&content->last_update);

    printf("%.6s ", str_time + 4);

    printf("%*.5s ", time_padding, str_time + (ft_strlen(str_time) - 14));

}

//http://manpagesfr.free.fr/man/man2/stat.2.html <- stat example
//https://www.mkssoftware.com/docs/man1/ls.1.asp <- long listing infos


int isNotRegularFile(unsigned char type) {
    return (type == DT_CHR || type == DT_SOCK || type == DT_BLK);
}

struct ls_padding handle_listing_padding(struct ls_node *dir_nodes, ls_options *options) {
    ls_node *it = dir_nodes;

    struct ls_padding paddings;
    ft_bzero(&paddings, sizeof(struct ls_padding));

    char *str_time = NULL;

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

        if (isNotRegularFile(it->content->type)) {

            int tmp_minor = get_number_len((int)it->content->minor);
            int tmp_major = get_number_len((int)it->content->major);

            if (paddings.minor_size < tmp_minor)
                paddings.minor_size = tmp_minor;

            if (paddings.major_size < tmp_major)
                paddings.major_size = tmp_major;

            if (paddings.major_size + paddings.minor_size + 2 > paddings.octet_size)
                paddings.octet_size = paddings.major_size + paddings.minor_size + 2;
        }

        str_time = ctime(&it->content->last_update);

        if (ft_strnstr(str_time, "2022", ft_strlen(str_time)) == NULL)
            paddings.time_size = 5;

        int tmp_blk_size = get_number_len(it->content->blocks);
        if (paddings.blocks_size < tmp_blk_size)
            paddings.blocks_size = tmp_blk_size;

        if (paddings.link_size < tmp_link_size)
            paddings.link_size = tmp_link_size;

        if (paddings.blocks_size)
            paddings.total_blocks += it->content->blocks;

        it = it->next;
    }
    return paddings;
}


void print_listing(ls_node *nodes, ls_options *options) {

    ls_node *it = nodes;

    struct ls_padding paddings = handle_listing_padding(nodes, options);

    if (options->not_print_total == 0)
        printf("total %lld\n", paddings.total_blocks);

    while (it)
    {

        if (!options->all && ft_strlen(it->content->name) && it->content->name[0] == '.') {
            it = it->next;
            continue;
        }

        if (options->blocks_size)
        {
            printf("%*ld ", paddings.blocks_size, it->content->blocks);
        }

        print_ls_perm_format(it->content);


        printf(" %*ld %*s ",
               paddings.link_size, it->content->nb_link,
               paddings.u_name_size, it->content->u_name);


        if (options->not_print_group == 0) {
            printf("%*s ", paddings.g_name_size, it->content->g_name);
        }

        if (isNotRegularFile(it->content->type)) {
            printf("%*u, %*u ", paddings.minor_size, it->content->major, paddings.major_size, it->content->minor);
        } else {
            printf("%*lld ", paddings.octet_size, it->content->octets);
        }

        print_ls_time_format(it->content, paddings.time_size);

//        if (it->content->type == DT_DIR) blue();
//        if (it->content->type == DT_LNK) cyan();

        const char quote = insert_quotes(it->content->name);
        if (quote)
            printf("%c", quote);
        printf("%s", it->content->name);
        if (quote)
            printf("%c", quote);

//        reset();

        if (ft_strlen(it->content->sym_link) > 0) {
            printf(" -> %s", it->content->sym_link);
        }

        putchar('\n');

        it = it->next;
    }

}
