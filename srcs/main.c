#include "../includes/ft_ls.h"


int main(int argc, char **argv)
{
    DIR *test = opendir(".");

    if (test) {

        struct dirent *files;
        files = readdir(test);

        printf("File %3d: %s\n", 0, files->d_name);
        printf("File %3d: %s\n", 0, files->d_name);
        printf("File %3d: %s\n", 0, files->d_name);

    }

}