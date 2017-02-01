#include "ft_ls.h"

static void ft_init_opt(t_env *e)
{
	e->options[0][0] = 'l';
	e->options[0][1] = 'a';
	e->options[0][2] = 'r';
	e->options[0][3] = 't';
	e->options[0][4] = 'R';

	e->options[1][0] = '0';
	e->options[1][1] = '0';
	e->options[1][2] = '0';
	e->options[1][3] = '0';
	e->options[1][4] = '0';
}

t_env *ft_init(void)
{
	t_env *e;
	int i;

	i = -1;
	if (!(e = (t_env *)malloc(sizeof(*e))))
		return (NULL);
	if (!(e->options = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	while (++i < 2)
	{
		if (!(e->options[i] = (char*)malloc(sizeof(char) * 6)))
			return (NULL);
		e->options[i][5] = '\0';
	}
	ft_init_opt(e);
	e->dir_lst = NULL;
	e->files_lst = NULL;
	return (e);
}

void 	ft_get_option(char **options, char *str)
{
	char *p;
	int i;

	p = str;
	while (*++p)
	{
		i = -1;
		while (++i < 5)
		{
			if (options[0][i] == *p)
			{
				options[1][i] += 1;
				break;
			}
			if (i == 4)
			{
				write(1, "usage: ls [-Ralrt] [file ...]\n", 30);
				exit(0);
			}
		}
	}
}

1/ FT_ASCII RCHR !!!!
2/ FT_INSERT_FILE !!!!
3/ TESTER!


int 	ft_insert_dir(t_env *e, char *dir_name)
{
	t_dir_lst *tmp;

	if (!(e->dir_lst))
	{
		e->dir_lst = ft_add_dir(dir_name, NULL, NULL);

		// if (!(e->dir_lst = (t_dir_lst *)malloc(sizeof(t_dir_lst))))
		// {
		// 	perror("ft_parse.c --> line 69 ");
		// 	exit(0);
		// }
		// e->dir_lst->d_name = dir_name;
		// if (!(e->dir_lst->dir = opendir(dir_name)))
		// {
		// 	perror("ft_parse.c --> line 75 ");
		// 	return (0);
		// }
	}
	else
	{
		tmp = ft_srch_ascii(e->dir_lst, dir_name);
		if(!(tmp->prev) && !(tmp->next) && tmp)
		{
			tmp->prev = ft_add_dir(dir_name, NULL, tmp);
		
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
}

t_env 	*ft_parse(int argc, char **argv)
{
	t_env *e;
	int i;

	e = ft_init();
	i = 0;
	if (argc == 1)
	{
		insert_dir(e->dir_lst, '.');
	}
	else
	{
		while (++i < argc)
		{
			if (argv[i][0] == '-')
				ft_get_option(e->options, argv[i]);
			else
			{
				if ((-1 == stat(argv[i], e->stat_tmp)))
				{
					perror("ls ");
				}
				else if ((S_ISDIR(e->stat_tmp->st_mode)))
				{
					ft_insert_dir(e, argv[i]);
					// arg_lst = ft_add_arg(argv[i]);
					// tmp = arg_lst;
					// tmp->prev = NULL;
				}
				else
				{
					ft_insert_file(e, argv[i]);
					// tmp->next = ft_add_arg(argv[i]);
					// tmp->next->prev = tmp;
					// tmp = tmp->next;
				}
		}
	}
	return (arg_lst);
}

t_arg *ft_add_dir(char *dir_name, t_dir_lst *prev, t_dir_lst *next)
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