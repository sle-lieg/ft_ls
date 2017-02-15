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
	*p++ = ' ';

	return (p);
}

char 	*ft_put_nb_lnk(t_env *e, char *p, t_files_lst *fil_lst)
{
	char *tmp;
	int len_max;
	int len;

	len_max = ft_strlen(ft_itoa(e->dir_lst->nb_lnk));
	tmp = ft_itoa(fil_lst->stat.st_nlink);
	len = ft_strlen(tmp);
	while (len++ < len_max)
		*p++ = ' ';
	while (tmp && *tmp)
		*p++ = *tmp++;
	*p++ = ' ';
	return (p);
}

char 	*ft_put_uid(t_env *e, char *p, t_files_lst *fil_lst)
{
	(void)e;

	struct passwd *passwd;

	passwd = getpwuid(fil_lst->stat.st_uid);
	ft_strcpy(p, passwd->pw_name);
	while (*p)
		p++;
	*p++ = ' ';
	return (p);
}

char 	*ft_put_gid(t_env *e, char *p, t_files_lst *fil_lst)
{
	(void)e;

	struct group *grp;
	grp = getgrgid(fil_lst->stat.st_gid);
	ft_strcpy(p, grp->gr_name);
	while (*p)
		p++;
	*p++ = ' ';
	return (p);
}

char 	*ft_put_size(t_env *e, char *p, t_files_lst *fil_lst)
{
	(void)e;

	char *tmp;

	tmp = ft_itoa(fil_lst->stat.st_size);
	if (tmp)
	{
		while (*tmp)
		{
			*p++ = *tmp++;
		}
	}
	*p++ = ' ';
	return (p);
}

char 	*ft_put_date(t_env *e, char *p, t_files_lst *fil_lst)
{
	(void)e;

	char *tmp;
	int i;

	tmp = ctime(&fil_lst->stat.st_mtimespec.tv_sec);
	i = 3;
	if (tmp)
	{
		while (++i < 16)
		{
			*p++ = *(tmp + i);
		}
	}
	*p++ = ' ';
	return (p);
}

char 	*ft_put_name(t_env *e, char *p, t_files_lst *fil_lst)
{
	(void)e;
	
	char 	tmp[512];
	int 	ret;
	
	ft_strcpy(p, fil_lst->f_name);
	if (S_ISLNK(fil_lst->stat.st_mode))
	{
		ft_bzero(&tmp, 512);
		while (*p)
			p++;
		ret = readlink(fil_lst->f_name, tmp, 512);
		{
			if (ret == -1)
				perror("");
			else
			{
				tmp[ret] = '\0';
				ft_strcpy(p, " -> ");
				p += 4;
				ft_strcpy(p, tmp);
			}
		}
	}
	return (p);
}


void 	ft_print_l(t_env *e, t_files_lst *fil_lst)
{
	char 			buff[512];
	char 			*p;

	ft_bzero(&buff, 512);
	p = buff;
	p = ft_put_mode(e, p, fil_lst);
	p = ft_put_nb_lnk(e, p, fil_lst);
	p = ft_put_uid(e, p, fil_lst);
	p = ft_put_gid(e, p, fil_lst);
	p = ft_put_size(e, p, fil_lst);
	p = ft_put_date(e, p, fil_lst);
	p = ft_put_name(e, p, fil_lst);

	ft_putstr(buff);	
	write(1, "\n", 1);
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
