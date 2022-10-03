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

typedef struct ls_content
{
    char *name;
    unsigned char type;

} ls_content;

typedef struct ls_node
{
    ls_content *content;
    char *dir_path;
    struct ls_node *subdir;
    struct ls_node *next;

} ls_node;

typedef struct ls_options
{
    int long_list;
    int recursive;
    int all;
    int rev;
    int sort_by_updated_time;
    char *base_path;
} ls_options;


/** ERRORS **/
void str_error(char *error);


/** PARSE DIR **/
ls_node *process_dir(DIR *dp, char *dir_path);
void lst_add_node_sort(ls_node **alst, ls_node *new);


/** ARGS **/
int parse_args(int argc, char **argv, ls_options *options);


/** OUTPUT **/
void simple_print(ls_node *dir_nodes);
void print_long_listing(char *str);


/** FREE **/
void free_nodes(ls_node *nodes);
void free_split(char **split);


/** RECURSIVE **/
void handle_recursive(ls_options *options);


/** LST UTILS **/
ls_node	*ls_lstnew(void *content);



#endif