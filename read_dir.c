#include "ft_ls.h"

int ft_read_dir(t_env *e, t_dir_lst *dir_lst)
{
	struct dirent 	*elem;
	char 			*path_name;

	path_name = NULL;
	if (!(dir_lst->dir = opendir(dir_lst->path)))
	{
		ft_putstr(dir_lst->path);
		write(1, "\nls: ", 5);
		perror(dir_lst->d_name);
		return(0);
	}
	while ((elem = readdir(dir_lst->dir)))
	{
		//path_name = ft_get_path(e, elem->d_name);
		path_name = ft_join_sep(dir_lst->path, elem->d_name, '/');
		if (!(lstat(path_name, &(e->stat_tmp))))
		{
			if ((S_ISDIR(e->stat_tmp.st_mode)
			 && e->options[1][4] > '0' && elem->d_name[0] != '.'))
			{
				ft_tmp_lst(e, elem->d_name, path_name);
			}
			ft_insert_file(e, elem->d_name);
			e->dir_lst->blocks_size += e->stat_tmp.st_blocks;
	
			//if (e->options[1][0] > '0')
			//	ft_get_limit(e);

			if (e->stat_tmp.st_nlink > dir_lst->nb_lnk &&
				(elem->d_name[0] != '.' || e->options[1][1] > '0'))
				dir_lst->nb_lnk = e->stat_tmp.st_nlink;
		}
		free(path_name);
	}
	// if (dir_lst->nb_lnk > 100)
	// 	dir_lst->nb_lnk = 100;
	// else if (dir_lst->nb_lnk > 10)
	// 	dir_lst->nb_lnk = 10;
	// else
	// 	dir_lst->nb_lnk = 0;
	// if (dir_lst->prev || dir_lst->next)
	// {
	// 	ft_putstr(dir_lst->path);
	// 	write(1, ":\n", 2);
	// }
	if (e->tmp_lst)
	{
		ft_merge_lst(e, dir_lst);
		e->tmp_lst = NULL;
	}
	return (0);
}

int 	ft_get_limit(e)
{
	
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

char *ft_join_sep(char *s1, char *s2, char c)
{
	char *new;
	char *p;

	if (!(new = (char*)malloc(sizeof(*s1) * ((ft_strlen(s1) + ft_strlen(s2) + 2)))))
		return(NULL);
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

char *ft_get_path(t_env *e, char *file_name)
{
	char *path_name;

	path_name = NULL;
	if (!(path_name = ft_join_sep(e->dir_lst->path, file_name, '/')))
	{
		perror("");
		exit(0);
	}
	return (path_name);
}