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

int contains_special_char(char *str) {
    int i = 0;
    while (str && str[i]) {

        char c = str[i];
        if (c == '`' || c == '~' || c == '#' || c == '$' || c == '&' || c == '*' || c == '(' || c == ')' || c == '\\' || c == '/' || c == '|'
            || c == '{' || c == '}' || c == '<' || c == '>' || c == '?' || c == '!' || c == ';' || c == '\'' || c == '"') {
            return (1);
        }
        i++;
    }
    return (0);
}

char insert_quotes(char *str) {

    char quote_type = 0;

    if (contains_special_char(str) == 1) {
        quote_type = '\'';
        if (ft_strchr(str, '\'') != NULL) {
            quote_type = '"';
        }
    }
    return quote_type;
}