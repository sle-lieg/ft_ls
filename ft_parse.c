#include "ft_ls.h"

t_arg *ft_parse(int argc, char **argv)
{
	t_arg *arg_lst;
	t_arg *tmp;
	int i;

	i = 0;

	arg_lst = NULL;
	tmp = NULL;
	if (argc == 1)
	{
		arg_lst = ft_add_arg(".");
		arg_lst->prev = NULL;
	}
	else
	{	
		while (++i < argc)
		{
			if (i == 1)
			{
				arg_lst = ft_add_arg(argv[i]);
				tmp = arg_lst;
				tmp->prev = NULL;
			}
			else
			{
				tmp->next = ft_add_arg(argv[i]);
				tmp->next->prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return (arg_lst);
}

t_arg *ft_add_arg(char *file_name)
{
	t_arg *arg;
	
	if (!(arg = (t_arg *)malloc(sizeof(t_arg))))
	{
		perror("error malloc arg_lst ");
		exit(0);
	}
/*	if (!(arg->file_lst = (t_dirent*)malloc(sizeof(t_dirent))))
	{
		perror("error malloc arg->file_lst ");
		exit(0);
	}*/
	arg->filename = ft_strdup(file_name);
	arg->next = NULL;
	arg->dir = NULL;
	arg->file_lst = NULL;
	return (arg);
}