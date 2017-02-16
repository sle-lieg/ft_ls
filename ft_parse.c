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

	e->modes[0] = S_IFREG;
	e->modes[1] = S_IFDIR;
	e->modes[2] = S_IFLNK;
	e->modes[3] = S_IFIFO;
	e->modes[4] = S_IFCHR;
	e->modes[5] = S_IFBLK;
	e->modes[6] = S_IFSOCK;

	e->modes_char[0] = '-';
	e->modes_char[1] = 'd';
	e->modes_char[2] = 'l';
	e->modes_char[3] = 'p';
	e->modes_char[4] = 'c';
	e->modes_char[5] = 'b';
	e->modes_char[6] = 's';	
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
	if (!(e->limit = (t_limit*)malloc(sizeof(t_limit))))
		return (NULL);
	ft_init_opt(e);
	e->dir_lst = NULL;
	e->fil_lst = NULL;
	e->tmp_lst = NULL;
	e->limit->len_lnk = 0;
	e->limit->len_uid = 0;
	e->limit->len_gid = 0;
	e->limit->len_size = 0;
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
				write(1, "ls: illegal option -- ", 22);
				write(1, p, 1);
				write(1, "\n", 1);
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
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			ft_get_option(e->options, argv[i]);
		else
		{
			if ((-1 == stat(argv[i], &(e->stat_tmp))))
			{
				write(1, "ls: ", 4);
				perror(argv[i]);
			}
			else
			{
				if ((S_ISDIR(e->stat_tmp.st_mode)))
				{
					ft_insert_dir(e, argv[i]);
				}
				else
				{
					ft_insert_file(e, argv[i]);
					if (e->options[1][0] > '0')
						ft_get_limit(e, argv[i]);
				}
			}
		}
	}
	if (!e->dir_lst && !e->fil_lst)
	{
		ft_insert_dir(e, ".");
	}
	return (e);
}