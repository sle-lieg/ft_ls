#include "ft_ls.h"

int ft_read_dir(t_env *e, t_dir_lst *dir_lst)
{
	struct dirent 	*elem;
	char 			*path_name;

	if (!(dir_lst->dir = opendir(dir_lst->path)))
	{
		ft_putstr(dir_lst->path);
		write(1, "\nls: ", 5);
		perror(dir_lst->d_name);
		return(0);
	}
	while ((elem = readdir(dir_lst->dir)))
	{
		path_name = ft_get_path(e, elem->d_name);
		if (!(lstat(path_name, &(e->stat_tmp))))
		{
			if ((S_ISDIR(e->stat_tmp.st_mode)/* && !(S_ISLNK(e->stat_tmp.st_mode)) && (e->stat_tmp.st_mode & (S_IRGRP | S_IROTH))*/
			 && e->options[1][4] > '0' && elem->d_name[0] != '.'))
			{
				ft_tmp_lst(e, elem->d_name, path_name);
			}
			ft_insert_file(e, elem->d_name);
			e->dir_lst->blocks_size += e->stat_tmp.st_blocks;
			if (e->stat_tmp.st_nlink > dir_lst->nb_lnk)
				dir_lst->nb_lnk = e->stat_tmp.st_nlink;
		}
	}
	if (dir_lst->nb_lnk > 100)
		dir_lst->nb_lnk = 100;
	else if (dir_lst->nb_lnk > 10)
		dir_lst->nb_lnk = 10;
	else
		dir_lst->nb_lnk = 0;
	if (dir_lst->prev || dir_lst->next)
	{
		ft_putstr(dir_lst->path);
		write(1, ":\n", 2);
	}
	if (e->tmp_lst)
	{
		ft_merge_lst(e, dir_lst);
		e->tmp_lst = NULL;
	}
	ft_print_files(e);
	return (0);
}

int 	ft_tmp_lst(t_env *e, char *dir_name, char *path_name)
{
	t_dir_lst *tmp;

	if (!(e->tmp_lst))
	{
		e->tmp_lst = ft_add_dir(path_name, dir_name, NULL, NULL);
	}
	else
	{
		if (e->options[1][2] > '0')
			tmp = ft_sort_drev(e->tmp_lst, dir_name);
		else
			tmp = ft_sort_d(e->tmp_lst, dir_name);
		if(tmp && !tmp->prev)
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
			{
				tmp = tmp->next;
			}
			tmp->next = ft_add_dir(path_name, dir_name, tmp, NULL);
		}
	}
	return (0);
}

int ft_merge_lst(t_env *e, t_dir_lst *dir_lst)
{
	t_dir_lst *tmp;

	tmp = e->tmp_lst;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	if (dir_lst->next)
	{
		dir_lst->next->prev = tmp;
		tmp->next = dir_lst->next;
	}
	dir_lst->next = e->tmp_lst;
	e->tmp_lst->prev = dir_lst;
	return (0);
}

char *ft_get_path(t_env *e, char *file_name)
{
	char path_name[500];
	char *tmp;
	int len;

	len = ft_strlen(e->dir_lst->path);
	ft_memcpy(path_name, e->dir_lst->path, len);
	if (path_name[len - 1] != '/')
		path_name[len] = '/';
	ft_memcpy(&(path_name + len + 1), file_name, ft_strlen);	

	/*path_name = e->dir_lst->path;
	tmp = path_name;
	if (*path_name != '/' || (*path_name == '/' && *(path_name + 1)))
		path_name = ft_strjoin(path_name, "/");
//	free(tmp);
	tmp = path_name;
	path_name = ft_strjoin(path_name, file_name);
//	free(tmp);*/
	return (path_name);
}