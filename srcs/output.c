#include "../includes/ft_ls.h"

int has_next_item(ls_options *options) {
    return (options->recursive || double_array_len(options->paths) > 1);
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

char insertQuotes(char *str) {

    char quote_type = 0;

    if (contains_special_char(str) == 1) {
        quote_type = '\'';
        if (ft_strchr(str, '\'') != NULL) {
            quote_type = '"';
        }
    }
    return quote_type;
}

void print_simple(ls_node *nodes, ls_options *options) {
    ls_node *it = nodes;

    while (it) {

        if (!options->all && ft_strlen(it->content->name) && it->content->name[0] == '.') {
            it = it->next;
            continue;
        }

        char quote = insertQuotes(it->content->name);

        if (quote)
            printf("%c", quote);
        printf("%s", it->content->name);
        if (quote)
            printf("%c", quote);

        it = it->next;
        if (it != NULL)
            printf("  ");

    }

    if (nodes) {
        printf("\n");
    }
}


void print_ls(ls_node *dir_nodes, char *path, ls_options *options) {

    if (has_next_item(options)) {
        printf("%s:\n", path);
    }

    if (options->long_list)
        print_listing(dir_nodes, options);
    else
        print_simple(dir_nodes, options);

}
