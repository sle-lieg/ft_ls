#include "ft_ls.h"

t_files_lst *ft_add_file(char *file_name, t_files_lst *prev, t_files_lst *next)
{
	t_files_lst *elem;
	
	if (!(elem = (t_files_lst *)malloc(sizeof(t_files_lst))))
	{
		perror("");
		exit(0);
	}
	elem->f_name = ft_strdup(file_name);
	elem->next = next;
	elem->prev = prev;
	return (elem);
}

t_files_lst *ft_sort_f(t_files_lst *files_lst, char *name)
{
	t_files_lst *tmp;

	tmp = files_lst;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->f_name) < 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return(NULL);
}

t_files_lst *ft_sort_frev(t_files_lst *files_lst, char *name)
{
	t_files_lst *tmp;

	tmp = files_lst;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->f_name) > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return(NULL);
}

int 	ft_insert_file(t_env *e, char *file_name)
{
	t_files_lst *tmp;

	if (!(e->fil_lst))
	{
		e->fil_lst = ft_add_file(file_name, NULL, NULL);
	}
	else
	{
		if (e->options[1][2] > '0')
			tmp = ft_sort_frev(e->fil_lst, file_name);
		else
			tmp = ft_sort_f(e->fil_lst, file_name);		
		if(tmp && !tmp->prev)
		{
			tmp->prev = ft_add_file(file_name, NULL, tmp);
			e->fil_lst = tmp->prev;
		}
		else if (tmp)
		{
			tmp->prev->next = ft_add_file(file_name, tmp->prev, tmp);
			tmp->prev = tmp->prev->next;
		}
		else
		{
			tmp = e->fil_lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ft_add_file(file_name, tmp, NULL);
		}

	}
	return(0);
}
