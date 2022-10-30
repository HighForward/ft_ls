#include "../includes/ft_ls.h"

int dir_is_not_dot(char *dir) {
    if (ft_strcmp(dir, ".") == 0 || ft_strcmp(dir, "..") == 0)
        return (1);
    return (0);
}

char *get_dir_path(char *curr_path, char *curr_dir) {

    char *tmp_str = NULL;

    size_t base_len = ft_strlen(curr_path);
    size_t dir_len = ft_strlen(curr_dir);
    size_t slash = 0;
    if (curr_path[base_len - 1] != '/' && dir_len > 0)
        slash = 1;

    const size_t tmp_len = base_len + dir_len + slash; //+1 for the slash

    tmp_str = ft_strnew(tmp_len);
    tmp_str = ft_strcat(tmp_str, curr_path);
    if (slash)
        tmp_str = ft_strcat(tmp_str, "/");
    if (dir_len)
        tmp_str = ft_strcat(tmp_str, curr_dir);
    return (tmp_str);
}


ls_content *alloc_content_struct() {

    ls_content *content = NULL;

    if (!(content = malloc(sizeof(struct ls_content)))) {
        return (NULL);
    }

    ft_bzero(content, sizeof(struct ls_content));

    return (content);
}

int exit_stat_error(char *path) {
    fprintf(stderr, "ls: cannot access '%s': %s\n", path, strerror(errno));
    free(path);
    return (EXIT_FAILURE);
}

int load_listing(ls_content *content, char *path) {

    if (content) {

        struct stat sb;
        ft_bzero(&sb, sizeof(struct stat));

        char *dir_path = get_dir_path(path, content->name);

        if (lstat(dir_path, &sb) < 0) {
            return exit_stat_error(path);
        }

        ssize_t len = readlink(dir_path, content->sym_link, sizeof(content->sym_link) - 1);
        if (len != -1) {
            content->sym_link[len] = '\0';
        }

        free(dir_path);

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

ls_node *process_dir(DIR *dp, char *path, ls_options *options) {

    ls_node *nodes = NULL;
    ls_content *content = NULL;

    struct dirent *dirp = NULL;

    while ((dirp = readdir(dp)) != NULL)
    {
        if (!options->all && ft_strlen(dirp->d_name) && dirp->d_name[0] == '.')
            continue;

        if (!(content = alloc_content_struct()))
            return (NULL);

        content->name = ft_strdup(dirp->d_name);
        content->type = dirp->d_type;

        if (load_data_and_insert_node(&nodes, content, path, options) == EXIT_FAILURE) {
            continue;
        }
    }

    return nodes;
}

int trigger_insert(ls_content *curr, ls_content *next, ls_options *options) {

    if (options->sort_by_updated_time) {
        return (!options->rev ?
            curr->last_update <= next->last_update : curr->last_update >= next->last_update);
    }
    if (options->sort_file_size) {
        return (!options->rev ?
                curr->octets <= next->octets : curr->octets >= next->octets);
    } else {
        return (!options->rev ?
            ft_strcmp_lower(curr->name, next->name) >= 0 : ft_strcmp_lower(curr->name, next->name) <= 0);
    }
}

void lst_add_node_sort(ls_node **alst, ls_node *new, ls_options *options)
{
    ls_node *curr = NULL;

    if (alst && new)
    {
        if (*alst == NULL)
            *alst = new;
        else
        {
            curr = (*alst);
            do
            {
                if (trigger_insert(curr->content, new->content, options))
                {
                    ls_node *tmp = curr->next;
                    curr->next = new;
                    new->next = tmp;

                    ls_content *test = curr->content;
                    curr->content = curr->next->content;
                    curr->next->content = test;
                    return ;
                } else if (curr->next == NULL) {
                    curr->next = new;
                    return ;
                }
                curr = curr->next;
            } while (curr != NULL) ;
        }
    }
}