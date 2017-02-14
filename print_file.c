#include "ft_ls.h"

char 	*ft_put_mode(t_env *e, char *p, t_files_lst *fil_lst)
{
	unsigned short 	test;
	int 		 	i;
	unsigned short 	mask;

	mask = 0x100;
	i = 0;
	test = fil_lst->stat.st_mode & S_IFMT;
	while (test != e->modes[i] && i < 7)
		i++;
	if (i < 7)
		*p++ = e->modes_char[i];
	else
	{
		write (1, "unknown file type", 17);
		exit(0);
	}
	*p++ = ((mask & fil_lst->stat.st_mode) ? 'r' : '-');
	*p++ = ((mask >> 1 & fil_lst->stat.st_mode) ? 'w' : '-');
	*p++ = ((mask >> 2 & fil_lst->stat.st_mode) ? 'x' : '-');

	*p++ = ((mask >> 3 & fil_lst->stat.st_mode) ? 'r' : '-');
	*p++ = ((mask >> 4 & fil_lst->stat.st_mode) ? 'w' : '-');
	*p++ = ((mask >> 5 & fil_lst->stat.st_mode) ? 'x' : '-');

	*p++ = ((mask >> 6 & fil_lst->stat.st_mode) ? 'r' : '-');
	*p++ = ((mask >> 7 & fil_lst->stat.st_mode) ? 'w' : '-');
	*p++ = ((mask >> 8 & fil_lst->stat.st_mode) ? 'x' : '-');

	*p++ = ' ';
	*p++ = '\n';

	//ft_putstr(buff);
	//write(1, "\n", 1);
	return (p);
}

/*char 	*ft_put_nb_lnk(t_env *e, char *p, t_files_lst *fil_lst)
{
	if (fil_lst->stat.st_nlink < e->dir_lst->nb_lnk)

	while (e->dir_lst->nb_lnk)
}*/

void 	ft_print_l(t_env *e, t_files_lst *fil_lst)
{
	char 			buff[512];
	char 			*p;

	ft_bzero(&buff, 512);
	p = buff;
	p = ft_put_mode(e, p, fil_lst);
	//p = ft_put_nb_lnk(e, p, fil_lst);
	ft_putstr(buff);	

	// print 
}

int		ft_print_files(t_env *e)
{
	t_files_lst *tmp;
	int 		printed;

	static char buff[4096];

	ft_bzero(buff, 4096);


	printed = 0;
	tmp = e->fil_lst;
	if (tmp && e->options[1][0] > '0')
	{
		write(1, "total ", 6);
		ft_putnbr(e->dir_lst->blocks_size);
		write(1, "\n", 1);
	}
	while (tmp)
	{
		if (tmp->f_name[0] != '.' || e->options[1][1] > '0')
		{
			if (e->options[1][0] > '0')
			{
				ft_print_l(e, tmp);
			}
			else
			{
				ft_putstr(tmp->f_name);
				write(1, " ", 1);
			}
			printed = 1;
		}
		tmp = tmp->next;
	}
	if (printed)
		write(1, "\n", 1);
	return (0);
}
