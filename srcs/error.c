#include "../includes/ft_ls.h"

void str_error(char *error) {
    perror(strerror(errno));
    exit(EXIT_FAILURE);
}