#include "ft_ls.h"

int ft_ls()
{
	return (0);
}

void 	ft_putarglst(t_arg *arg_lst)
{
	t_arg *tmp;

	tmp = arg_lst;
	while (tmp)
	{
		ft_putstr(tmp->filename);
		write(1, " ", 1);
		tmp = tmp->next;
	}
}

void ft_delete_arg(t_arg *false_arg)
{
	t_arg *tmp;

	tmp = false_arg;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(false_arg->filename);
	free(false_arg);
}

int	ft_open_arg_lst(t_arg *arg_lst)
{
	t_arg *tmp;

	tmp = arg_lst;
	while (tmp)
	{

	}
	return (0);
}

int main(int argc, char **argv)
{
	t_env e;

	if (!(e = ft_parse(argc, argv)))
		return (-1);
	ft_open_arg_lst(e);

	ft_putarglst(arg_lst);
	ft_ls();
	return (0);
}