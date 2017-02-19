/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:10:29 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:10:42 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_lst	*ft_add_dir(char *path, char *d_name, t_dir_lst *pr, t_dir_lst *nx)
{
	t_dir_lst *elem;

	if (!(elem = (t_dir_lst *)malloc(sizeof(t_dir_lst))))
	{
		perror("");
		exit(0);
	}
	elem->d_name = ft_strdup(d_name);
	elem->next = nx;
	elem->prev = pr;
	elem->dir = NULL;
	elem->blocks_size = 0;
	elem->path = ft_strdup(path);
	return (elem);
}

t_dir_lst	*ft_sort_d(t_dir_lst *dir_lst, char *name)
{
	t_dir_lst *tmp;

	tmp = dir_lst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->d_name) < 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_dir_lst	*ft_sort_drev(t_dir_lst *dir_lst, char *name)
{
	t_dir_lst *tmp;

	tmp = dir_lst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->d_name) > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		ft_sort_dir(t_env *e, char *dir_name)
{
	t_dir_lst *tmp;

	if (e->options[1][2] > '0')
		tmp = ft_sort_drev(e->dir_lst, dir_name);
	else
		tmp = ft_sort_d(e->dir_lst, dir_name);
	if (tmp && !tmp->prev)
	{
		tmp->prev = ft_add_dir(dir_name, dir_name, NULL, tmp);
		e->dir_lst = tmp->prev;
	}
	else if (tmp)
	{
		tmp->prev->next = ft_add_dir(dir_name, dir_name, tmp->prev, tmp);
		tmp->prev = tmp->prev->next;
	}
	else
	{
		tmp = e->dir_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_add_dir(dir_name, dir_name, tmp, NULL);
	}
}

int			ft_insert_dir(t_env *e, char *dir_name)
{
	if (!(e->dir_lst))
		e->dir_lst = ft_add_dir(dir_name, dir_name, NULL, NULL);
	else
		ft_sort_dir(e, dir_name);
	return (0);
}
