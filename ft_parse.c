/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:11:33 by sle-lieg          #+#    #+#             */
/*   Updated: 2017/02/18 20:19:16 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_init_opt(t_env *e)
{
	ft_strcpy(e->options[0], "lartR1d");
	ft_memset(e->options[1], '0', 7);
	ft_strcpy(e->modes_char, "-dlpcbs");
	e->modes[0] = S_IFREG;
	e->modes[1] = S_IFDIR;
	e->modes[2] = S_IFLNK;
	e->modes[3] = S_IFIFO;
	e->modes[4] = S_IFCHR;
	e->modes[5] = S_IFBLK;
	e->modes[6] = S_IFSOCK;
	e->check_if_arg = 0;
}

t_env			*ft_init(void)
{
	t_env	*e;
	int		i;

	i = -1;
	if (!(e = (t_env *)malloc(sizeof(*e))))
		return (NULL);
	if (!(e->options = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	while (++i < 2)
	{
		if (!(e->options[i] = (char*)malloc(sizeof(char) * 7)))
			return (NULL);
		e->options[i][7] = '\0';
	}
	if (!(e->limit = (t_limit*)malloc(sizeof(t_limit))))
		return (NULL);
	ft_init_opt(e);
	ft_reset_limit(e);
	e->dir_lst = NULL;
	e->fil_lst = NULL;
	e->tmp_lst = NULL;
	return (e);
}

void			ft_get_option(char **options, char *str)
{
	int		i;

	while (*++str)
	{
		i = -1;
		while (++i < 7)
		{
			if (options[0][i] == *str)
			{
				options[1][i] = '1';
				if (options[0][i] == 'l')
					options[1][5] = '0';
				else if (options[0][i] == '1')
					options[1][0] = '0';
				break ;
			}
			if (i == 6)
			{
				write(2, "ls: illegal option -- ", 22);
				write(2, str, 1);
				write(2, "\nusage: ls [-Radlrt1] [file ...]\n", 33);
				exit(0);
			}
		}
	}
}

void			ft_get_argv(t_env *e, char *argv)
{
	if ((-1 == lstat(argv, &(e->stat_tmp))))
	{
		write(1, "ls: ", 4);
		perror(argv);
	}
	else
	{
		e->tmp_name = ft_strdup(argv);
		if ((S_ISDIR(e->stat_tmp.st_mode) && e->options[1][6] == '0') || (S_ISLNK(e->stat_tmp.st_mode) > 0 && e->options[1][0] == '0'))
			ft_insert_dir(e);
		else
		{
			ft_insert_file(e);
			if (e->options[1][0] > '0')
				ft_get_limit(e);
		}
	}
	e->check_if_arg = 1;
}

t_env			*ft_parse(int argc, char **argv)
{
	t_env	*e;
	int		i;
	int 	end_opt;

	e = ft_init();
	i = 0;
	end_opt = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			end_opt = 1;
		else if (argv[i][0] == '-' && !end_opt)
			ft_get_option(e->options, argv[i]);
		else
			ft_get_argv(e, argv[i]);
	}
	if (!e->tmp_lst && !e->fil_lst && !e->check_if_arg)
	{
		e->tmp_name = ".";
		if (e->options[1][6] == '0')
			ft_insert_dir(e);
		else
			ft_insert_file(e);
	}
	if (e->tmp_lst)
	{
		e->dir_lst = e->tmp_lst;
		e->tmp_lst = NULL;
	}
	return (e);
}