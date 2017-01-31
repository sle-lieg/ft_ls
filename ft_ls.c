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
		if ((stat(tmp->filename, tmp->arg_details) == -1))
		{
			write(1, "ls: ", 4);
			ft_putstr(tmp->filename);
			perror("");
			tmp = tmp->next;
			ft_delete_arg(tmp->prev);
		}
		else 
		{
			if (S_ISDIR(tmp->arg_details->st_mode))
			{
				if (!(tmp->dir = opendir(tmp->filename)))
					perror("error opendir ");
			}
			else if (S_ISREG(tmp->arg_details->st_mode))
			{
				ft_putstr(tmp->filename);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_arg *arg_lst;

	if (!(arg_lst = ft_parse(argc, argv)))
		return (-1);
	ft_open_arg_lst(arg_lst);

	ft_putarglst(arg_lst);
	ft_ls();
	return (0);
}