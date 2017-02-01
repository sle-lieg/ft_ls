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

typedef struct 	s_dirent
{
	struct dirent 	*file;
	struct s_dirent *next;
}				t_dirent;

typedef struct s_files_lst
{
	char 				*f_name;
	struct stat 		*stat_buf;
	struct s_files_lst 	*next;
	struct s_files_lst 	*prev;

}				t_files_lst;

typedef struct s_dir_lst
{
	char 				*d_name;
	DIR 				*dir;
	struct stat 		*stat_buf;
	struct s_dir_lst 	*next;
	struct s_dir_lst 	*prev;

}				t_dir_lst;

typedef struct 	s_env
{
	char **options;
//	struct s_arg *arg_lst;
	struct s_dir_lst 	*dir_lst;
	struct s_files_lst 	*fil_lst;
	struct stat 		*stat_tmp;

}				t_env;

/* ***** ft_parse ***** */
t_env 		*ft_parse(int argc, char **argv);
void 		ft_get_option(char **options, char *str);
t_env 		*ft_init(void);

/* ***** ft_create_lst ***** */
int 		ft_insert_dir(t_env *e, char *dir_name);
int 		ft_insert_file(t_env *e, char *file_name);
t_dir_lst 	*ft_sort(t_dir_lst *dir_lst, char *name);
t_dir_lst 	*ft_sort_drev(t_dir_lst *dir_lst, char *name);
t_dir_lst 	*ft_add_dir(char *dir_name, t_dir_lst *prev, t_dir_lst *next);
t_files_lst	*ft_add_file(char *file_name, t_files_lst *prev, t_files_lst *next);

t_files_lst *ft_sort_frev(t_files_lst *files_lst, char *name);
t_files_lst *ft_sort_f(t_files_lst *files_lst, char *name);



/* ***** ft_ls.c ***** */
// int	ft_open_arg_lst(t_arg *arg_lst);
// void ft_delete_arg(t_arg *false_arg);



#endif