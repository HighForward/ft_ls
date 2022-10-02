#ifndef FT_LS
#define FT_LS

#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#include <sys/stat.h>
#include <time.h>

#include <grp.h>

void print_node(char *str);
void print_long_listing(char *str);
void file_stat(char *path);


void str_error(char *error);

typedef struct ls_content {
    char *name;
} ls_content ;

//typedef struct ls_node {
//
//    ls_content *content;
//    struct ls_node *next;
//    struct ls_node *prev;
//
//} ls_node;



#endif