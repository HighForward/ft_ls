#include "../includes/ft_ls.h"

void print_long_listing(char *str) {

    struct stat sb;


    if (stat(str, &sb) == -1) {
        str_error("stat");
    }

    char *ctime_ret = ctime(&sb.st_mtime);

    char **ctime_split = ft_split(ctime_ret,' ');

    struct group *gp = getgrgid(sb.st_gid);

    printf("RIGHTS %ld %s %s %lld %s %s %s %s\n",
           (long) sb.st_nlink, gp->gr_name, gp->gr_name, (long long) sb.st_size, ctime_split[1], ctime_split[2], ctime_split[3], str);

    free_split(ctime_split);
}
