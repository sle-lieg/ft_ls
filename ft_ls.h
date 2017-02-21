/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:11:17 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:34:57 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include "libft/libft.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))

typedef struct	s_limit
{
	int					len_lnk;
	int					len_uid;
	int					len_gid;
	int					len_size;
	int					len_major;
	int					len_minor;
}				t_limit;

typedef struct	s_files_lst
{
	long int 			f_time;

	char				*f_name;
	struct stat			stat;
	struct s_files_lst	*next;
	struct s_files_lst	*prev;

}				t_files_lst;

typedef struct	s_dir_lst
{
	long int 			d_time;

	char				*d_name;
	char				*path;
	off_t				blocks_size;
	DIR					*dir;
	struct s_dir_lst	*next;
	struct s_dir_lst	*prev;
}				t_dir_lst;

typedef struct	s_env
{
	int 				check_if_arg;
	char				**options;
	struct s_limit		*limit;
	struct s_dir_lst	*dir_lst;
	struct s_files_lst	*fil_lst;
	struct s_dir_lst	*tmp_lst;
	struct stat			stat_tmp;
	unsigned int		modes[7];
	char				modes_char[7];
	char 				*tmp_name;
}				t_env;

/*
 * ***** ft_parse *****
*/
t_env			*ft_parse(int argc, char **argv);
t_env			*ft_init(void);
void			ft_get_option(char **options, char *str);
void			ft_get_argv(t_env *e, char *argv);

/*
 * ***** ft_fil_lst *****
*/
// int				ft_insert_file(t_env *e, char *file_name);
// t_files_lst		*ft_add_file(t_env *e, char *fnam,\
// 				t_files_lst *pr, t_files_lst *nx);
// t_files_lst		*ft_sort_fascii(t_env *e, char *name);
// t_files_lst 	*ft_sort_ftime(t_env *e, long int time, char *name);
// void			ft_sort_file(t_env *e, char *file_name);
int				ft_insert_file(t_env *e);
t_files_lst		*ft_add_file(t_env *e, t_files_lst *pr, t_files_lst *nx);
t_files_lst		*ft_sort_fascii(t_env *e);
t_files_lst 	*ft_sort_ftime(t_env *e, long int time);
void			ft_sort_file(t_env *e);

/*
 * ***** ft_dir_lst *****
*/

// int				ft_insert_dir(t_env *e, char *dir_name);
// t_dir_lst 		*ft_sort_time(t_env *e, long int time, char *dir_name);
// t_dir_lst		*ft_sort_ascii(t_env *e, char *name);
// t_dir_lst		*ft_add_dir(t_env *e, char *path, char *d_name,\
// 				t_dir_lst *pr, t_dir_lst *nx);
// void			ft_sort_dir(t_env *e, char *dir_name);
int				ft_insert_dir(t_env *e);
t_dir_lst 		*ft_sort_time(t_env *e, long int time);
t_dir_lst		*ft_sort_ascii(t_env *e);
t_dir_lst		*ft_add_dir(t_env *e, char *path, t_dir_lst *pr, t_dir_lst *nx);
void			ft_sort_dir(t_env *e);

/*
 * ***** read_dir.c *****
*/
// int				ft_read_dir(t_env *e, t_dir_lst *dir_lst);
// int				ft_tmp_lst(t_env *e, char *dir_name, char *path_name);
// void			ft_read(t_env *e, t_dir_lst *dir_lst);
// void			ft_tmp(t_env *e, char *dir_name, char *path_name);
// void			ft_get_limit(t_env *e);
int				ft_read_dir(t_env *e, t_dir_lst *dir_lst);
int				ft_tmp_lst(t_env *e, char *path_name);
void			ft_read(t_env *e, t_dir_lst *dir_lst);
void			ft_tmp(t_env *e, char *path_name);
void			ft_get_limit(t_env *e);

/*
 * ***** read_dir2.c *****
*/
int				ft_merge_lst(t_env *e, t_dir_lst *dir_lst);
char			*ft_join_sep(char *s1, char *s2, char c);
char 			*ft_put_dev_id(t_env *e, char *p, t_files_lst *fil_lst);

/*
 * ***** print_file.c *****
*/
char			*ft_put_mode(t_env *e, char *p, t_files_lst *fil_lst);
char			*ft_put_nb_lnk(t_env *e, char *p, t_files_lst *fil_lst);
void			ft_print_l(t_env *e, t_files_lst *fil_lst);
void			ft_print(t_env *e, t_files_lst *tmp, int dir, int *printed);
int				ft_print_files(t_env *e, int dir);

/*
 * ***** print_file.c *****
*/
char			*ft_put_uid(t_env *e, char *p, t_files_lst *fil_lst);
char			*ft_put_gid(t_env *e, char *p, t_files_lst *fil_lst);
char			*ft_put_size(t_env *e, char *p, t_files_lst *fil_lst);
char			*ft_put_date(char *p, t_files_lst *fil_lst);
char			*ft_put_name(t_env *e, char *p, t_files_lst *fil_lst);

/*
 * ***** ft_ls.c *****
*/
void			ft_reset_tmp_lst(t_dir_lst *tmp_lst);
void			ft_destroy_dir(t_dir_lst *dir);
void			ft_destroy_fil_lst(t_env *e);
void			ft_reset_limit(t_env *e);

#endif
