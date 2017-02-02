#include "ft_ls.h"

void 	ft_putlst(t_env *e)
{
	t_dir_lst *tmp;
	t_files_lst *tmp2;

	tmp = e->dir_lst;
	tmp2 = e->fil_lst;

	while (tmp2)
	{
		ft_putstr(tmp2->f_name);
		write(1, " ", 1);
		tmp2 = tmp2->next;
	}
	write(1, "\n", 1);
	while (tmp)
	{
		ft_putstr(tmp->d_name);
		write(1, " ", 1);
		tmp = tmp->next;
	}
}

// void ft_delete_arg(t_arg *false_arg)
// {
// 	t_arg *tmp;

// 	tmp = false_arg;
// 	if (tmp->prev)
// 		tmp->prev->next = tmp->next;
// 	if (tmp->next)
// 		tmp->next->prev = tmp->prev;
// 	free(false_arg->filename);
// 	free(false_arg);
// }

// int	ft_open_arg_lst(t_arg *arg_lst)
// {
// 	t_arg *tmp;

// 	tmp = arg_lst;
// 	while (tmp)
// 	{

// 	}
// 	return (0);
// }

// int ft_ls(t_env *e)
// {
// 	ft_print_files(e->fil_lst);

// 	return (0);
// }

int main(int argc, char **argv)
{
	t_env *e;

	if (!(e = ft_parse(argc, argv)))
		return (-1);
	//ft_open_arg_lst(e);

	ft_putlst(e);
//	ft_ls(e);
	return (0);
}