/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:48:10 by sle-lieg          #+#    #+#             */
/*   Updated: 2016/11/19 01:37:50 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_inittab2(char **ptr, const char *s, char c)
{
	int i;
	int j;
	int dim;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		dim = 0;
		while (s[i] != c && s[i])
		{
			dim++;
			i++;
		}
		if (dim)
		{
			ptr[j] = (char *)malloc(sizeof(char) * dim + 1);
			if (!ptr[j])
				return (NULL);
			j++;
		}
		if (s[i])
			i++;
	}
	return (ptr);
}

static char		**ft_inittab1(const char *s, char c)
{
	int		i;
	int		count;
	char	**tab;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count += 1;
		i++;
	}
	tab = (char **)malloc(sizeof(*tab) * count + 1);
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	ft_inittab2(tab, s, c);
	if (!tab)
		return (NULL);
	return (tab);
}

static void		ft_fillarray(char **tab, const char *s, char c)
{
	int i;
	int j;
	int p;

	i = 0;
	j = 0;
	p = 0;
	while (s && s[i])
	{
		while (s[i] == c && s[i])
		{
			p = 0;
			i++;
		}
		while (s[i] != c && s[i])
		{
			tab[j][p] = s[i];
			p++;
			i++;
		}
		if (tab[j])
			tab[j][p] = '\0';
		j++;
	}
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		pos;
	char	**tab;

	pos = 0;
	i = 0;
	tab = ft_inittab1(s, c);
	if (!tab)
		return (NULL);
	ft_fillarray(tab, s, c);
	return (tab);
}
