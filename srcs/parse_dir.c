#include "../includes/ft_ls.h"

int dir_is_not_dot(char *dir) {
    if (ft_strcmp(dir, ".") == 0 || ft_strcmp(dir, "..") == 0)
        return (1);
    return (0);
}

char *get_dir_path(char *curr_path, char *curr_dir) {

    char *tmp_str = NULL;
    const int tmp_len = (int)ft_strlen(curr_path) + (int)ft_strlen(curr_dir) + 1; //+1 for the slash

    tmp_str = ft_strnew(tmp_len);
    tmp_str = ft_strcat(tmp_str, curr_path);
    tmp_str = ft_strcat(tmp_str, "/");
    tmp_str = ft_strcat(tmp_str, curr_dir);
    return (tmp_str);
}


ls_content *load_dir_data(struct dirent *dir) {

    ls_content *content = NULL;

    if (!(content = malloc(sizeof(struct ls_content)))) {
        return (NULL);
    }

    ft_bzero(content, sizeof(struct ls_content));
    content->name = dir->d_name;
    content->type = dir->d_type;
    content->g_name = NULL;
    content->u_name = NULL;

    return (content);
}

int load_listing(ls_content *content, char *path) {

    if (content) {
        struct stat sb;
        ft_bzero(&sb, sizeof(struct stat));

        char *dir_path = get_dir_path(path, content->name);

        if (content->type == DT_LNK) {

            if (lstat(dir_path, &sb) < 0) {
                printf("ls: cannot access '%s': Permission denied\n", dir_path);
                free(dir_path);
                return (EXIT_FAILURE);
            }
            ssize_t len = readlink(dir_path, content->sym_link, sizeof(content->sym_link) - 1);
            if (len != -1) {
                content->sym_link[len] = '\0';
            }

        } else {
            if (stat(dir_path, &sb) < 0) {
                printf("ls: cannot access '%s': Permission denied\n", dir_path);
                free(dir_path);
                return (EXIT_FAILURE);
            }
        }


        free(dir_path);

        struct passwd* puid = getpwuid(sb.st_uid);
        struct group* guid = getgrgid(sb.st_gid);
        struct group* group = getgrgid(guid->gr_gid);

        content->nb_link = sb.st_nlink;
        content->u_name = puid->pw_name;


        content->g_name = ft_strdup(guid->gr_name);

        content->octets = sb.st_size;
        content->blksize = sb.st_blksize;
        content->blocks = sb.st_blocks / 2;
        content->perm = sb.st_mode;
        content->last_update = sb.st_mtime;
    }
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

        if (!(content = load_dir_data(dirp)))
            return (NULL);

        if (load_listing(content, path)) {
            free(content);
            continue;
        }

        ls_node *tmp_new = ls_lstnew(content);


        lst_add_node_sort(&nodes, tmp_new, options);
    }

    return nodes;
}

int trigger_insert(ls_content *curr, ls_content *next, ls_options *options) {

    if (options->sort_by_updated_time) {
        return (!options->rev ?
            curr->last_update <= next->last_update : curr->last_update >= next->last_update);
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

                    // swap content
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