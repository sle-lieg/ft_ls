/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 21:15:02 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/23 01:10:00 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_put_uid(t_env *e, char *p, t_files_lst *fil_lst)
{
	struct passwd	*passwd;
	int				len;

	passwd = getpwuid(fil_lst->stat.st_uid);
	len = ft_strlen(passwd->pw_name);
	ft_strcpy(p, passwd->pw_name);
	p += len;
	while (len++ < e->limit->len_uid)
		*p++ = ' ';
	*p++ = ' ';
	*p++ = ' ';
	return (p);
}

char	*ft_put_gid(t_env *e, char *p, t_files_lst *fil_lst)
{
	struct group	*grp;
	int				len;

	grp = getgrgid(fil_lst->stat.st_gid);
	len = ft_strlen(grp->gr_name);
	ft_strcpy(p, grp->gr_name);
	p += len;
	while (len++ < e->limit->len_gid)
		*p++ = ' ';
	*p++ = ' ';
	*p++ = ' ';
	return (p);
}

char	*ft_put_size(t_env *e, char *p, t_files_lst *fil_lst)
{
	char	*tmp;
	int		len;
	int		len_max;

	if (!(tmp = ft_itoa(fil_lst->stat.st_size)))
	{
		ft_putstr("error malloc.\n");
		exit(0);
	}
	len = ft_strlen(tmp);
	if ((e->dir_lst && !ft_str_is_inc(e->dir_lst->path, "/dev"))
		|| (!e->dir_lst && !ft_str_is_inc(fil_lst->f_name, "/dev")))
		len_max = e->limit->len_size;
	else
		len_max = e->limit->len_minor + e->limit->len_major + 3;
	while (len++ < len_max)
		*p++ = ' ';
	while (*tmp)
		*p++ = *tmp++;
	*p++ = ' ';
	return (p);
}

char	*ft_put_date(char *p, t_files_lst *fil_lst)
{
	char		*tmp;
	int			i;
	long int	today;
	time_t		t;

	tmp = ctime(&fil_lst->stat.st_mtimespec.tv_sec);
	today = time(&t);
	i = 3;
	if (tmp)
	{
		while (++i < 11)
			*p++ = *(tmp + i);
	}
	if (ABS(today - fil_lst->stat.st_mtimespec.tv_sec) > 15552000)
	{
		*p++ = ' ';
		i = 19;
		while (++i < 24)
			*p++ = *(tmp + i);
	}
	else
	{
		i = 10;
		while (++i < 16)
			*p++ = *(tmp + i);
	}
	*p++ = ' ';
	return (p);
}

char	*ft_put_name(t_env *e, char *p, t_files_lst *fil_lst)
{
	char	tmp[512];
	char	*path;
	int		ret;

	ft_strcpy(p, fil_lst->f_name);
	if (S_ISLNK(fil_lst->stat.st_mode))
	{
		ft_bzero(&tmp, 512);
		while (*p)
			p++;
		if (e->dir_lst)
			path = ft_join_sep(e->dir_lst->path, fil_lst->f_name, '/');
		else
			path = ft_join_sep(NULL, fil_lst->f_name, '/');
		ret = readlink(path, tmp, 512);
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
	return (p);
}
