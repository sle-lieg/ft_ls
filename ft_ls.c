#include "ft_ls.h"

// void ft_reset_tmp_lst(t_dir_lst *tmp_lst)
// {
// 	t_dir_lst *tmp;

// 	while (tmp_lst)
// 	{
// 		tmp = tmp_lst;
// 		tmp_lst = tmp_lst->next;
// 		tmp->d_name = NULL;
// 		tmp->prev = NULL;
// 		tmp->next = NULL;
// 		tmp->dir = NULL;
// 	}
// 	tmp_lst = NULL;
// }

int ft_ls(t_env *e)
{
	t_dir_lst *tmp;

	tmp = e->dir_lst;
	ft_print_files(e);
	if (e->fil_lst)
		write(1, "\n", 1);
	while (tmp)
	{
		if (e->fil_lst)
			ft_destroy_fil_lst(e);
		ft_read_dir(e, tmp);
		if (tmp->prev || tmp->next)
		{
			ft_putstr(tmp->path);
			write(1, ":\n", 2);
		}
		ft_print_files(e);
		e->dir_lst = e->dir_lst->next;
		ft_destroy_dir(tmp);
		tmp = e->dir_lst;
		//ft_reset_tmp_lst(e->tmp_lst);
		if (tmp)
			write(1, "\n", 1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_env *e;

	if (!(e = ft_parse(argc, argv)))
		return (-1);
	//ft_open_arg_lst(e);

//	ft_putlst(e);
	ft_ls(e);
	return (0);
}