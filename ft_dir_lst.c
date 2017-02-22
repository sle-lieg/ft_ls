/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:10:29 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/23 00:38:49 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_lst	*ft_add_dir(t_env *e, char *path, t_dir_lst *pr, t_dir_lst *nx)
{
	t_dir_lst *elem;

	if (!(elem = (t_dir_lst *)malloc(sizeof(t_dir_lst))))
	{
		perror("");
		exit(0);
	}
	elem->d_name = ft_strdup(e->tmp_name);
	elem->next = nx;
	elem->prev = pr;
	elem->dir = NULL;
	elem->blocks_size = 0;
	elem->path = ft_strdup(path);
	elem->d_time = e->stat_tmp.st_mtimespec.tv_sec;
	return (elem);
}

t_dir_lst	*ft_sort_ascii(t_env *e)
{
	t_dir_lst	*tmp;

	tmp = e->tmp_lst;
	if (e->options[1][2] > '0')
	{
		while (tmp)
		{
			if (ft_strcmp(e->tmp_name, tmp->d_name) > 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (ft_strcmp(e->tmp_name, tmp->d_name) < 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

t_dir_lst	*ft_sort_time(t_env *e, long int time)
{
	t_dir_lst	*tmp;

	tmp = e->tmp_lst;
	if (e->options[1][2] > '0')
	{
		while (tmp)
		{
			if (time < tmp->d_time ||
			(time == tmp->d_time && ft_strcmp(e->tmp_name, tmp->d_name) > 0))
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (time > tmp->d_time ||
			(time == tmp->d_time && ft_strcmp(e->tmp_name, tmp->d_name) < 0))
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void		ft_sort_dir(t_env *e)
{
	t_dir_lst *tmp;

	if (e->options[1][3] == '0')
		tmp = ft_sort_ascii(e);
	else
		tmp = ft_sort_time(e, e->stat_tmp.st_mtimespec.tv_sec);
	if (tmp && !tmp->prev)
	{
		tmp->prev = ft_add_dir(e, e->tmp_name, NULL, tmp);
		e->tmp_lst = tmp->prev;
	}
	else if (tmp)
	{
		tmp->prev->next = ft_add_dir(e, e->tmp_name, tmp->prev, tmp);
		tmp->prev = tmp->prev->next;
	}
	else
	{
		tmp = e->tmp_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_add_dir(e, e->tmp_name, tmp, NULL);
	}
}

int			ft_insert_dir(t_env *e)
{
	if (!(e->tmp_lst))
		e->tmp_lst = ft_add_dir(e, e->tmp_name, NULL, NULL);
	else
		ft_sort_dir(e);
	return (0);
}
