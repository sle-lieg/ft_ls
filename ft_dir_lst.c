#include "ft_ls.h"

t_dir_lst *ft_add_dir(char *dir_name, t_dir_lst *prev, t_dir_lst *next)
{
	t_dir_lst *elem;
	
	if (!(elem = (t_dir_lst *)malloc(sizeof(t_dir_lst))))
	{
		perror("");
		exit(0);
	}
	elem->d_name = ft_strdup(dir_name);
	elem->next = next;
	elem->prev = prev;
	if (!(elem->dir = opendir(dir_name)))
	{
		perror("ft_parse.c --> line 162 ");
	}
	return (elem);
}

t_dir_lst *ft_sort_d(t_dir_lst *dir_lst, char *name)
{
	t_dir_lst *tmp;

	tmp = dir_lst;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->d_name) < 0)
			return (tmp);
		tmp = tmp->next;
	}
	return(NULL);
}

t_dir_lst *ft_sort_drev(t_dir_lst *dir_lst, char *name)
{
	t_dir_lst *tmp;

	tmp = dir_lst;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->d_name) > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return(NULL);
}



int 	ft_insert_dir(t_env *e, char *dir_name)
{
	t_dir_lst *tmp;

	if (!(e->dir_lst))
	{
		e->dir_lst = ft_add_dir(dir_name, NULL, NULL);
	}
	else
	{
		if (e->options[1][2] > '0')
			tmp = ft_sort_drev(e->dir_lst, dir_name);
		else
			tmp = ft_sort_d(e->dir_lst, dir_name);
		if(tmp && !tmp->prev)
		{
			tmp->prev = ft_add_dir(dir_name, NULL, tmp);
			e->dir_lst = tmp->prev;
		}
		else if (tmp)
		{
			tmp->prev->next = ft_add_dir(dir_name, tmp->prev, tmp);
			tmp->prev = tmp->prev->next;
		}
		else
		{
			tmp = e->dir_lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ft_add_dir(dir_name, tmp, NULL);
		}
	}
	return (0);
}
