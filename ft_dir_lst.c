#include "ft_ls.h"

t_dir_lst *ft_add_dir(char *path_name, char *dir_name, t_dir_lst *prev, t_dir_lst *next)
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
	elem->dir = NULL;
	elem->blocks_size = 0;
	elem->nb_lnk = 0;
	elem->path = ft_strdup(path_name);
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
		e->dir_lst = ft_add_dir(dir_name, dir_name, NULL, NULL);
	}
	else
	{
		if (e->options[1][2] > '0')
			tmp = ft_sort_drev(e->dir_lst, dir_name);
		else
			tmp = ft_sort_d(e->dir_lst, dir_name);
		if(tmp && !tmp->prev)
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
	return (0);
}

void ft_destroy_dir(t_dir_lst *dir)
{
	if (dir->d_name)
		free(dir->d_name);
	if (dir->dir && (-1 == (closedir(dir->dir))))
		perror("ft_ls.c --> line 117 ");
	if (dir)
		free(dir);
}