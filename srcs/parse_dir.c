#include "../includes/ft_ls.h"

int dir_is_not_dot(char *dir) {
    if (ft_strncmp(dir, ".", ft_strlen(dir)) == 0 || ft_strncmp(dir, "..", ft_strlen(dir)) == 0)
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

    return (content);
}

void load_listing(ls_content *content, char *path) {

    if (content) {
        struct stat sb;
        ft_bzero(&sb, sizeof(struct stat));

        char *dir_path = get_dir_path(path, content->name);

        if (stat(dir_path, &sb) < 0) {
            str_error("error stat");
        }

        free(dir_path);

        content->nb_link = 1;
        content->u_name = getpwuid(sb.st_uid)->pw_name;
        content->g_name = getgrgid(sb.st_gid)->gr_name;
        content->octets = sb.st_size;
        get_ls_time_format(content, sb.st_ctime);
    }
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

        if (options->long_list) {
            load_listing(content, path);
        }

        ls_node *tmp_new = ls_lstnew(content);


        lst_add_node_sort(&nodes, tmp_new);
    }

//    free(dp);
    return nodes;
}

void lst_add_node_sort(ls_node **alst, ls_node *new)
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
                if (ft_strncmp(curr->content->name, new->content->name, ft_strlen(new->content->name)) > 0)
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