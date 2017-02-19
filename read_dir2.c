/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 21:39:03 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 22:45:10 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_merge_lst(t_env *e, t_dir_lst *dir_lst)
{
	t_dir_lst *tmp;

	tmp = e->tmp_lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (dir_lst->next)
	{
		dir_lst->next->prev = tmp;
		tmp->next = dir_lst->next;
	}
	dir_lst->next = e->tmp_lst;
	e->tmp_lst->prev = dir_lst;
	return (0);
}

char	*ft_join_sep(char *s1, char *s2, char c)
{
	char *new;
	char *p;

	if (!(new = (char*)malloc(sizeof(*s1) *
		((ft_strlen(s1) + ft_strlen(s2) + 2)))))
		return (NULL);
	p = new;
	if (s1)
	{
		while (*s1)
			*p++ = *s1++;
	}
	if (*(p - 1) != c)
		*p++ = c;
	if (s2)
	{
		while (*s2)
			*p++ = *s2++;
	}
	*p = '\0';
	return (new);
}
