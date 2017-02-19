/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fil_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:10:59 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:17:32 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files_lst	*ft_add_file(t_env *e, char *fnam, t_files_lst *pr, t_files_lst *nx)
{
	t_files_lst *elem;

	if (!(elem = (t_files_lst *)malloc(sizeof(t_files_lst))))
	{
		perror("");
		exit(0);
	}
	elem->f_name = ft_strdup(fnam);
	elem->next = nx;
	elem->prev = pr;
	elem->stat = e->stat_tmp;
	return (elem);
}

t_files_lst	*ft_sort_f(t_files_lst *files_lst, char *name)
{
	t_files_lst *tmp;

	tmp = files_lst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->f_name) < 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_files_lst	*ft_sort_frev(t_files_lst *files_lst, char *name)
{
	t_files_lst *tmp;

	tmp = files_lst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->f_name) > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		ft_sort_file(t_env *e, char *file_name)
{
	t_files_lst *tmp;

	if (e->options[1][2] > '0')
		tmp = ft_sort_frev(e->fil_lst, file_name);
	else
		tmp = ft_sort_f(e->fil_lst, file_name);
	if (tmp && !tmp->prev)
	{
		tmp->prev = ft_add_file(e, file_name, NULL, tmp);
		e->fil_lst = tmp->prev;
	}
	else if (tmp)
	{
		tmp->prev->next = ft_add_file(e, file_name, tmp->prev, tmp);
		tmp->prev = tmp->prev->next;
	}
	else
	{
		tmp = e->fil_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_add_file(e, file_name, tmp, NULL);
	}
}

int			ft_insert_file(t_env *e, char *file_name)
{
	if (!(e->fil_lst))
		e->fil_lst = ft_add_file(e, file_name, NULL, NULL);
	else
		ft_sort_file(e, file_name);
	return (0);
}
