#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include "libft/libft.h"

typedef struct 	s_buf
{
	char buff[5000];
	char *p;

}				t_buf;

typedef struct s_files_lst
{
	char 				*f_name;
	struct stat 		stat;
	struct s_files_lst 	*next;
	struct s_files_lst 	*prev;

}				t_files_lst;

typedef struct s_dir_lst
{
	char 				*d_name;
	char 				*path;
	off_t 				blocks_size;
	nlink_t 			nb_lnk;
	DIR 				*dir;
	struct s_dir_lst 	*next;
	struct s_dir_lst 	*prev;

}				t_dir_lst;

typedef struct 	s_env
{
	char **options;
//	struct s_arg *arg_lst;
	struct s_dir_lst 	*dir_lst;
	struct s_files_lst 	*fil_lst;
	struct s_dir_lst 	*tmp_lst;
	struct stat 		stat_tmp;
	unsigned int 		modes[7];
	char 				modes_char[7];
}				t_env;

/* ***** ft_parse ***** */
t_env 		*ft_parse(int argc, char **argv);
void 		ft_get_option(char **options, char *str);
t_env 		*ft_init(void);

/* ***** ft_fil_lst ***** */
int 		ft_insert_file(t_env *e, char *file_name);
t_files_lst	*ft_add_file(t_env *e, char *file_name, t_files_lst *prev, t_files_lst *next);
t_files_lst *ft_sort_frev(t_files_lst *files_lst, char *name);
t_files_lst *ft_sort_f(t_files_lst *files_lst, char *name);
void 		ft_destroy_fil_lst(t_env *e);

/* ***** ft_dir_lst ***** */
int 		ft_insert_dir(t_env *e, char *dir_name);
t_dir_lst 	*ft_sort_d(t_dir_lst *dir_lst, char *name);
t_dir_lst 	*ft_sort_drev(t_dir_lst *dir_lst, char *name);
t_dir_lst 	*ft_add_dir(char *path_name, char *dir_name, t_dir_lst *prev, t_dir_lst *next);
void 		ft_destroy_dir(t_dir_lst *dir);

/* ***** read_dir.c ***** */
int 		ft_read_dir(t_env *e, t_dir_lst *dir_lst);
int 		ft_tmp_lst(t_env *e, char *dir_name, char *path_name);
int 		ft_merge_lst(t_env *e, t_dir_lst *dir_lst);
char 		*ft_get_path(t_env *e, char *file_name);
char 		*ft_join_sep(char *s1, char *s2, char c);


/* ***** print_file.c ***** */
int			ft_print_files(t_env *e);
void 		ft_print_l(t_env *e, t_files_lst *fil_lst);
char 		*ft_put_mode(t_env *e, char *p, t_files_lst *fil_lst);
char 		*ft_put_nb_lnk(t_env *e, char *p, t_files_lst *fil_lst);
char 		*ft_put_uid(t_env *e, char *p, t_files_lst *fil_lst);


/* ***** ft_ls.c ***** */
void 		ft_reset_tmp_lst(t_dir_lst *tmp_lst);


// int	ft_open_arg_lst(t_arg *arg_lst);
// void ft_delete_arg(t_arg *false_arg);



#endif