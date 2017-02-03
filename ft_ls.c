#include "ft_ls.h"

// void ft_delete_arg(t_arg *false_arg)
// {
// 	t_arg *tmp;

// 	tmp = false_arg;
// 	if (tmp->prev)
// 		tmp->prev->next = tmp->next;
// 	if (tmp->next)
// 		tmp->next->prev = tmp->prev;
// 	free(false_arg->filename);
// 	free(false_arg);
// }
 
int		ft_print_files(t_env *e)
{
	t_files_lst *tmp;

	tmp = e->fil_lst;
	while (tmp)
	{
		if (tmp->f_name[0] != '.' || e->options[1][1] > '0')
		{
			ft_putstr(tmp->f_name);
			write(1, " ", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// CHANGER LES INSERT PAR DES ADD !!

// char *ft_get_path_name(char *s1, char c, char *s2)
// {

// }

int 	ft_tmp_lst(t_env *e, char *dir_name)
{
	t_dir_lst *tmp;
	//char *path_name;

//	path_name = ft_get_path_name(e->dir_lst->d_name, '/', dir_name);
	if (!(e->tmp_lst))
	{
		e->tmp_lst = ft_add_dir(dir_name, NULL, NULL);
	}
	else
	{
		if (e->options[1][2] > '0')
			tmp = ft_sort_drev(e->tmp_lst, dir_name);
		else
			tmp = ft_sort_d(e->tmp_lst, dir_name);
		if(tmp && !tmp->prev)
		{
			tmp->prev = ft_add_dir(dir_name, NULL, tmp);
			e->tmp_lst = tmp->prev;
		}
		else if (tmp)
		{
			tmp->prev->next = ft_add_dir(dir_name, tmp->prev, tmp);
			tmp->prev = tmp->prev->next;
		}
		else
		{
			tmp = e->tmp_lst;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = ft_add_dir(dir_name, tmp, NULL);
		}
		printf("--%s\n", tmp->d_name);	
	//	printf("--%s\n", tmp->next->d_name);	

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

int ft_read_dir(t_env *e, t_dir_lst *dir_lst)
{
	struct dirent *elem;

	printf("++%s\n", dir_lst->d_name);	
	if (!(dir_lst->dir = opendir(dir_lst->d_name)))
	{
		perror("ft_ls.c --> line 95 ");
		return(0);
	}
	while ((elem = readdir(dir_lst->dir)))
	{
		stat(elem->d_name, &(e->stat_tmp));
		if ((S_ISDIR(e->stat_tmp.st_mode) && e->options[1][4] > '0' && (e->options[1][1] > '0' || elem->d_name[0] != '.')))
		{
			ft_tmp_lst(e, elem->d_name);
			printf("+-%s\n", e->tmp_lst->d_name);
			if (e->tmp_lst->next)
				printf("+-%s\n", e->tmp_lst->next->d_name);
		}
		ft_insert_file(e, elem->d_name);
	}
	if (dir_lst->prev || dir_lst->next)
	{
		ft_putstr(dir_lst->d_name);
		write(1, ":\n", 2);
	}
	if (e->tmp_lst)
	{
		ft_merge_lst(e, dir_lst);
		//ft_reset_tmp_lst(e->tmp_lst);
	}
	ft_print_files(e);
	return (0);
}

void ft_destroy_dir(t_dir_lst *dir)
{
	if (dir->d_name)
		free(dir->d_name);
	if (-1 == (closedir(dir->dir)))
		perror("ft_ls.c --> line 117 ");
	//free(dir);
}

void ft_reset_tmp_lst(t_dir_lst *tmp_lst)
{
	t_dir_lst *tmp;

	while (tmp_lst)
	{
		tmp = tmp_lst;
		tmp_lst = tmp_lst->next;
		tmp->d_name = NULL;
		tmp->prev = NULL;
		tmp->next = NULL;
		tmp->dir = NULL;
	}
	tmp_lst = NULL;
}

void ft_destroy_fil_lst(t_env *e)
{
	t_files_lst *tmp;

	while (e->fil_lst)
	{
		tmp = e->fil_lst;
		e->fil_lst = e->fil_lst->next;
		if (tmp->f_name)
			free(tmp->f_name);
		free(tmp);
	}
	e->fil_lst = NULL;
}

int ft_ls(t_env *e)
{
	t_dir_lst *tmp;

	tmp = e->dir_lst;
	ft_print_files(e);
	while (tmp)
	{
		if (e->fil_lst)
			ft_destroy_fil_lst(e);
		ft_read_dir(e, tmp);
		e->dir_lst = e->dir_lst->next;
		ft_destroy_dir(tmp);
		tmp = e->dir_lst;
		//ft_reset_tmp_lst(e->tmp_lst);
		if (tmp)
			write(1, "\n", 1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_env *e;

	if (!(e = ft_parse(argc, argv)))
		return (-1);
	//ft_open_arg_lst(e);

//	ft_putlst(e);
	ft_ls(e);
	return (0);
}