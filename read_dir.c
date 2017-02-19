/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:11:57 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:43:15 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_read_dir(t_env *e, t_dir_lst *dir_lst)
{
	if (!(dir_lst->dir = opendir(dir_lst->path)))
	{
		if (dir_lst->next)
		{
			ft_putstr(dir_lst->path);
			write(1, ":\n", 2);
		}
		write(2, "ls: ", 4);
		perror(dir_lst->d_name);
		return (0);
	}
	ft_read(e, dir_lst);
	if (e->tmp_lst)
	{
		ft_merge_lst(e, dir_lst);
		e->tmp_lst = NULL;
	}
	return (0);
}

void	ft_read(t_env *e, t_dir_lst *dir_lst)
{
	struct dirent	*elem;
	char			*path_name;

	elem = NULL;
	path_name = NULL;
	while ((elem = readdir(dir_lst->dir)))
	{
		path_name = ft_join_sep(dir_lst->path, elem->d_name, '/');
		if (!(lstat(path_name, &(e->stat_tmp))))
		{
			if ((S_ISDIR(e->stat_tmp.st_mode)
			&& e->options[1][4] > '0' && elem->d_name[0] != '.'))
				ft_tmp_lst(e, elem->d_name, path_name);
			ft_insert_file(e, elem->d_name);
			if (elem->d_name[0] != '.'
			|| (elem->d_name[0] == '.' && e->options[1][1] > '0'))
				e->dir_lst->blocks_size += e->stat_tmp.st_blocks;
			if (e->options[1][0] > '0')
				ft_get_limit(e, elem->d_name);
		}
		free(path_name);
	}
}

void	ft_get_limit(t_env *e, char *name)
{
	struct passwd	*password;
	struct group	*grp;
	int				len;

	len = ft_strlen(ft_itoa(e->stat_tmp.st_nlink));
	if (len > e->limit->len_lnk && (*name != '.' || e->options[1][1] > '0'))
		e->limit->len_lnk = len;
	password = getpwuid(e->stat_tmp.st_uid);
	len = ft_strlen(password->pw_name);
	if (len > e->limit->len_uid && (*name != '.' || e->options[1][1] > '0'))
		e->limit->len_uid = len;
	grp = getgrgid(e->stat_tmp.st_gid);
	len = ft_strlen(grp->gr_name);
	if (len > e->limit->len_gid && (*name != '.' || e->options[1][1] > '0'))
		e->limit->len_gid = len;
	len = ft_strlen(ft_itoa(e->stat_tmp.st_size));
	if (len > e->limit->len_size && (*name != '.' || e->options[1][1] > '0'))
		e->limit->len_size = len;
}

void	ft_tmp(t_env *e, char *dir_name, char *path_name)
{
	t_dir_lst *tmp;

	if (e->options[1][2] > '0')
		tmp = ft_sort_drev(e->tmp_lst, dir_name);
	else
		tmp = ft_sort_d(e->tmp_lst, dir_name);
	if (tmp && !tmp->prev)
	{
		tmp->prev = ft_add_dir(path_name, dir_name, NULL, tmp);
		e->tmp_lst = tmp->prev;
	}
	else if (tmp)
	{
		tmp->prev->next = ft_add_dir(path_name, dir_name, tmp->prev, tmp);
		tmp->prev = tmp->prev->next;
	}
	else
	{
		tmp = e->tmp_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_add_dir(path_name, dir_name, tmp, NULL);
	}
}

int		ft_tmp_lst(t_env *e, char *dir_name, char *path_name)
{
	if (!(e->tmp_lst))
		e->tmp_lst = ft_add_dir(path_name, dir_name, NULL, NULL);
	else
		ft_tmp(e, dir_name, path_name);
	return (0);
}
