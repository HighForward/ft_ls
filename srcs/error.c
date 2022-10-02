#include "../includes/ft_ls.h"

void str_error(char *error) {
    perror(error);
    exit(EXIT_FAILURE);
}