/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fil_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:10:59 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/23 00:51:20 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files_lst	*ft_add_file(t_env *e, t_files_lst *pr, t_files_lst *nx)
{
	t_files_lst *elem;

	if (!(elem = (t_files_lst *)malloc(sizeof(t_files_lst))))
	{
		perror("");
		exit(0);
	}
	elem->f_name = ft_strdup(e->tmp_name);
	elem->next = nx;
	elem->prev = pr;
	elem->stat = e->stat_tmp;
	return (elem);
}

t_files_lst	*ft_sort_fascii(t_env *e)
{
	t_files_lst	*tmp;

	tmp = e->fil_lst;
	if (e->options[1][2] > '0')
	{
		while (tmp)
		{
			if (ft_strcmp(e->tmp_name, tmp->f_name) > 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (ft_strcmp(e->tmp_name, tmp->f_name) < 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

t_files_lst	*ft_sort_ftime(t_env *e, long int time)
{
	t_files_lst	*tmp;

	tmp = e->fil_lst;
	if (e->options[1][2] > '0')
	{
		while (tmp)
		{
			if (time < tmp->stat.st_mtimespec.tv_sec ||
			(time == tmp->stat.st_mtimespec.tv_sec &&
			ft_strcmp(e->tmp_name, tmp->f_name) > 0))
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (time > tmp->stat.st_mtimespec.tv_sec ||
			(time == tmp->stat.st_mtimespec.tv_sec &&
			ft_strcmp(e->tmp_name, tmp->f_name) < 0))
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void		ft_sort_file(t_env *e)
{
	t_files_lst *tmp;

	if (e->options[1][3] == '0')
		tmp = ft_sort_fascii(e);
	else
		tmp = ft_sort_ftime(e, e->stat_tmp.st_mtimespec.tv_sec);
	if (tmp && !tmp->prev)
	{
		tmp->prev = ft_add_file(e, NULL, tmp);
		e->fil_lst = tmp->prev;
	}
	else if (tmp)
	{
		tmp->prev->next = ft_add_file(e, tmp->prev, tmp);
		tmp->prev = tmp->prev->next;
	}
	else
	{
		tmp = e->fil_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_add_file(e, tmp, NULL);
	}
}

int			ft_insert_file(t_env *e)
{
	if (!(e->fil_lst))
		e->fil_lst = ft_add_file(e, NULL, NULL);
	else
		ft_sort_file(e);
	return (0);
}
