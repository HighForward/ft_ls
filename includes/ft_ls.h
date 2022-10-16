#ifndef FT_LS
#define FT_LS

#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include <sys/stat.h>
#include <time.h>

#include <grp.h>
#include <pwd.h>

#define LS_TIME_SIZE 40

typedef struct ls_content
{
    char *name;
    unsigned char type;
    int nb_link;
    char *u_name;
    char *g_name;
    long long octets;
    __blksize_t blksize;
    __blkcnt_t blocks;
    __mode_t perm;
    __time_t last_update;
    char sym_link[PATH_MAX];

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
    int blocks_size;
    int not_print_group;
    int sort_file_size;
    char *base_path;
    char **paths;
} ls_options;


/** ERRORS **/
void str_error(char *error);


/** PARSE DIR **/
int dir_is_not_dot(char *dir);
char *get_dir_path(char *curr_path, char *curr_dir);
ls_node *process_dir(DIR *dp, char *path, ls_options *options);
void lst_add_node_sort(ls_node **alst, ls_node *new, ls_options *options);
int load_listing(ls_content *content, char *path);
ls_content *load_dir_data();

/** ARGS **/
int parse_args(int argc, char **argv, ls_options *options);


/** OUTPUT **/
void print_ls(ls_node *dir_nodes, char *path, ls_options *options);
void print_listing(ls_node *nodes, ls_options *options);

/** FORMAT **/
void get_ls_time_format(ls_content *content, time_t time);

/** FREE **/
void free_nodes(ls_node *nodes);
void free_split(char **split);


/** RECURSIVE **/


/** LST UTILS **/
ls_node	*ls_lstnew(void *content);

/** UTILS **/
char *ft_strcat(char *dst, char *to_cat);
int	ft_strcmp(char *s1, char *s2);
int	ft_strcmp_lower(char *s1, char *s2);
int getDoubleArrayLen(char **arr);

/** COLORS **/
void yellow();
void blue();
void cyan();
void reset();

#endif