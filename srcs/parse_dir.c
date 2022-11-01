#include "../includes/ft_ls.h"

int exit_stat_error(char *path) {
    fprintf(stderr, "ls: cannot access '%s': %s\n", path, strerror(errno));
    return (EXIT_FAILURE);
}

int load_listing(ls_content *content, char *path) {

    if (content) {

        struct stat sb;
        ft_bzero(&sb, sizeof(struct stat));

        if (lstat(path, &sb) < 0) {
            return exit_stat_error(path);
        }

        ssize_t len = readlink(path, content->sym_link, sizeof(content->sym_link) - 1);
        if (len != -1) {
            content->sym_link[len] = '\0';
        }

        struct passwd* puid = getpwuid(sb.st_uid);
        struct group* guid = getgrgid(sb.st_gid);
        struct group* group = NULL;


        if (puid) {
            content->u_name = puid->pw_name;
        }

        if (guid && guid->gr_gid) {
            group = getgrgid(guid->gr_gid);
            content->g_name = ft_strdup(group->gr_name);
        } else if (guid) {
            content->g_name = ft_strdup(guid->gr_name);
        }

        content->major = major(sb.st_rdev);
        content->minor = minor(sb.st_rdev);

        content->nb_link = sb.st_nlink;
        content->octets = sb.st_size;
        content->blksize = sb.st_blksize;
        content->blocks = sb.st_blocks / 2;
        content->perm = sb.st_mode;
        content->last_update = sb.st_mtime;
    }
    return (EXIT_SUCCESS);
}

int load_data_and_insert_node(ls_node **nodes, ls_content *content, char* path, ls_options *options) {

    if (load_listing(content, path)) {
        if (content->name)
            free(content->name);
        free(content);
        return (EXIT_FAILURE);
    }

    ls_node *tmp_new = ls_lstnew(content);
    lst_add_node_sort(nodes, tmp_new, options);
    return (EXIT_SUCCESS);
}

int process_dir(DIR *dp, char *path, ls_node **nodes, ls_options *options) {

    ls_content *content = NULL;

    struct dirent *dirp = NULL;

    while ((dirp = readdir(dp)) != NULL)
    {
        if (!options->all && ft_strlen(dirp->d_name) && dirp->d_name[0] == '.')
            continue;

        if (!(content = alloc_content_struct()))
            return (EXIT_FAILURE);

        content->name = ft_strdup(dirp->d_name);
        content->type = dirp->d_type;

        char *full_path = get_dir_path(path, content->name);

        if (load_data_and_insert_node(nodes, content, full_path, options) == EXIT_FAILURE) {
            free(full_path);
            continue;
        }

        free(full_path);
    }
    return (EXIT_SUCCESS);
}