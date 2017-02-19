/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:11:49 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:38:30 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_put_mode(t_env *e, char *p, t_files_lst *fil_lst)
{
	unsigned short	test;
	int				i;
	unsigned short	mask;

	mask = 0x100;
	i = 0;
	test = fil_lst->stat.st_mode & S_IFMT;
	while (test != e->modes[i] && i < 7)
		i++;
	if (i < 7)
		*p++ = e->modes_char[i];
	else
		exit(0);
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

char	*ft_put_nb_lnk(t_env *e, char *p, t_files_lst *fil_lst)
{
	char	*tmp;
	int		len;

	if (!(tmp = ft_itoa(fil_lst->stat.st_nlink)))
	{
		ft_putstr("error malloc.\n");
		exit(0);
	}
	len = ft_strlen(tmp);
	while (len++ < e->limit->len_lnk)
		*p++ = ' ';
	while (*tmp)
		*p++ = *tmp++;
	*p++ = ' ';
	return (p);
}

void	ft_print_l(t_env *e, t_files_lst *fil_lst)
{
	char buff[512];
	char *p;

	printf("%s\n", e->dir_lst->d_name);
	ft_bzero(&buff, 512);
	p = buff;
	p = ft_put_mode(e, p, fil_lst);
	p = ft_put_nb_lnk(e, p, fil_lst);
	p = ft_put_uid(e, p, fil_lst);
	p = ft_put_gid(e, p, fil_lst);
	p = ft_put_size(e, p, fil_lst);
	p = ft_put_date(p, fil_lst);
	p = ft_put_name(e, p, fil_lst);
	ft_putstr(buff);
	write(1, "\n", 1);
}

void	ft_print(t_env *e, t_files_lst *tmp, int dir, int *printed)
{
	if (e->options[1][0] > '0' && e->options[1][5] == '0')
	{
		if (!*printed && dir)
		{
			write(1, "total ", 6);
			ft_putnbr(e->dir_lst->blocks_size);
			write(1, "\n", 1);
		}
		ft_print_l(e, tmp);
	}
	else
	{
		ft_putstr(tmp->f_name);
		if (e->options[1][5] > '0' || (e->options[1][5] == '0' && !tmp->next))
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
	*printed = 1;
}

int		ft_print_files(t_env *e, int dir)
{
	t_files_lst	*tmp;
	int			printed;

	printed = 0;
	tmp = e->fil_lst;
	while (tmp)
	{
		if (tmp->f_name[0] != '.' || e->options[1][1] > '0' || e->options[1][6] > '0')
			ft_print(e, tmp, dir, &printed);
		tmp = tmp->next;
	}
	ft_reset_limit(e);
	return (0);
}
