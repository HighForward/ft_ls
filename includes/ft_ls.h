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
#include <pwd.h>

typedef struct ls_content
{
    char *name;
    unsigned char type;

} ls_content;

typedef struct ls_node
{
    ls_content *content;
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
int dir_is_not_dot(char *dir);
char *get_dir_path(char *curr_path, char *curr_dir);
ls_node *process_dir(DIR *dp, ls_options *options);
void lst_add_node_sort(ls_node **alst, ls_node *new);


/** ARGS **/
int parse_args(int argc, char **argv, ls_options *options);


/** OUTPUT **/
void print_ls(ls_node *dir_nodes, char *path, ls_options *options);
void print_long_listing(char *str);


/** FREE **/
void free_nodes(ls_node *nodes);
void free_split(char **split);


/** RECURSIVE **/


/** LST UTILS **/
ls_node	*ls_lstnew(void *content);


/** UTILS **/
char *ft_strcat(char *dst, char *to_cat);

#endif