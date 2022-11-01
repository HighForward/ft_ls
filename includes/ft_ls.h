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

#include <sys/sysmacros.h>


#include <grp.h>
#include <pwd.h>

#define LS_TIME_SIZE 40

typedef struct ls_content
{
    char *name;
    __mode_t type;
    unsigned long nb_link;
    char *u_name;
    char *g_name;
    long long octets;
    __blksize_t blksize;
    __blkcnt_t blocks;
    __mode_t perm;
    __time_t last_update;

    unsigned int major;
    unsigned int minor;
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

struct ls_padding {
    int link_size;
    int u_name_size;
    int g_name_size;
    int octet_size;
    int time_size;
    int blocks_size;
    long long total_blocks;
    int minor_size;
    int major_size;
};

/** ALLOC **/
ls_node	*ls_lstnew(void *content);
ls_content *alloc_content_struct();

/** PARSE DIR **/
int dir_is_not_dot(char *dir);
char *get_dir_path(char *curr_path, char *curr_dir);
int process_dir(DIR *dp, char *path, ls_node **nodes, ls_options *options);
void lst_add_node_sort(ls_node **alst, ls_node *new, ls_options *options);
int load_listing(ls_content *content, char *path);
ls_content *alloc_content_struct();
int load_data_and_insert_node(ls_node **nodes, ls_content *content, char* path, ls_options *options);


/** DIR UTILS **/
int dir_is_not_dot(char *dir);
char *get_dir_path(char *curr_path, char *curr_dir);
int contains_special_char(char *str);
char insert_quotes(char *str);


/** NODES INSERTS **/
int trigger_insert(ls_content *curr, ls_content *next, ls_options *options);
void lst_add_node_sort(ls_node **alst, ls_node *new, ls_options *options);

/** ARGS **/
int parse_args(int argc, char **argv, ls_options *options);


/** OUTPUT **/
void print_ls(ls_node *dir_nodes, char *path, ls_options *options);
void print_listing(ls_node *nodes, ls_options *options);
int has_next_item(ls_options *options);
char insert_quotes(char *str);


/** FREE **/
void free_nodes(ls_node *nodes);
void free_ptr(void *ptr);


/** UTILS **/
char *ft_strcat(char *dst, char *to_cat);
int	ft_strcmp(char *s1, char *s2);
int	ft_strcmp_lower(char *s1, char *s2);
int double_array_len(char **arr);
int get_number_len(int nb);

/** COLORS **/
void yellow();
void blue();
void cyan();
void reset();

#endif