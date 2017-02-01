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
	e->fil_lst = NULL;
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

t_env 	*ft_parse(int argc, char **argv)
{
	t_env *e;
	int i;

	e = ft_init();
	i = 0;
	if (argc == 1)
	{
		ft_insert_dir(e, ".");
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
	}
	return (e);
}
