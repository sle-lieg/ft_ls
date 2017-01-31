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

typedef struct 	s_arg
{
	char 			*filename;
	DIR 			*dir;
	struct stat 	*arg_details;
	struct s_dirent *file_lst;
	struct s_arg 	*next;
	struct s_arg 	*prev;
}				t_arg;

t_arg *ft_parse(int argc, char **argv);
t_arg *ft_add_arg(char *file_name);
int	ft_open_arg_lst(t_arg *arg_lst);
void ft_delete_arg(t_arg *false_arg);



#endif