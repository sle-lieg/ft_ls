/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:11:08 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/20 19:10:43 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(t_env *e)
{
	t_dir_lst *tmp;

	tmp = e->dir_lst;
	if (e->fil_lst)
		ft_print_files(e, 0);
	if (e->fil_lst && e->dir_lst)
		write(1, "\n", 1);
	while (tmp)
	{
		if (e->fil_lst || e->dir_lst->next)
		{
			ft_putstr(tmp->path);
			write(1, ":\n", 2);
		}
		if (e->fil_lst)
			ft_destroy_fil_lst(e);
		ft_read_dir(e, tmp);
		ft_print_files(e, 1);
		e->dir_lst = e->dir_lst->next;
		ft_destroy_dir(tmp);
		tmp = e->dir_lst;
		if (tmp)
			write(1, "\n", 1);
	}
	return (0);
}

void	ft_reset_limit(t_env *e)
{
	e->limit->len_lnk = 0;
	e->limit->len_uid = 0;
	e->limit->len_gid = 0;
	e->limit->len_size = 0;
	e->limit->len_major = 0;
	e->limit->len_minor = 0;
}

void	ft_destroy_fil_lst(t_env *e)
{
	t_files_lst *tmp;

	while (e->fil_lst)
	{
		tmp = e->fil_lst;
		e->fil_lst = e->fil_lst->next;
		// if (tmp->f_name)
		// 	free(tmp->f_name);
		// if (tmp)
			// free(tmp);
	}
	e->fil_lst = NULL;
}

void	ft_destroy_dir(t_dir_lst *dir)
{
	// if (dir->d_name)
	// 	free(dir->d_name);
	if (dir->dir && (-1 == (closedir(dir->dir))))
		perror("ft_ls.c --> line 117 ");
	// if (dir)
	// 	free(dir);
}

int		main(int argc, char **argv)
{
	t_env *e;

	if (!(e = ft_parse(argc, argv)))
		return (-1);
	ft_ls(e);
	return (0);
}
