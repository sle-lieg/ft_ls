/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 21:15:02 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:40:24 by sle-lieg         ###   ########.fr       */
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

	if (!(tmp = ft_itoa(fil_lst->stat.st_size)))
	{
		ft_putstr("error malloc.\n");
		exit(0);
	}
	len = ft_strlen(tmp);
	while (len++ < e->limit->len_size)
		*p++ = ' ';
	while (*tmp)
		*p++ = *tmp++;
	*p++ = ' ';
	return (p);
}

char	*ft_put_date(char *p, t_files_lst *fil_lst)
{
	char	*tmp;
	int		i;

	tmp = ctime(&fil_lst->stat.st_mtimespec.tv_sec);
	i = 3;
	if (tmp)
	{
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
		path = ft_join_sep(e->dir_lst->path, fil_lst->f_name, '/');
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
