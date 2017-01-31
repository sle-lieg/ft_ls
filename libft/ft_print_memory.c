/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 18:05:34 by sle-lieg          #+#    #+#             */
/*   Updated: 2016/12/12 16:04:28 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_hexaconv(void *nb)
{
	const char tab[] = "0123456789ABCDEF";
	unsigned char	*tmp;
	char	str[10] = {0, 0, 0, 0,' ', 0, 0, 0, 0,' '};
	int		pow;
	int		i;
	int		j;
	unsigned char	mask = 0xF;
	char	*tmp2 = 0;

	i = 0;
	j = 0;
	pow = 16;
	tmp = (unsigned char*)nb;
	str[1] = *tmp & mask;
	str[0] = *tmp >> 4 & mask;
	while (i < 10)
	{
		if (str[i] < 16)
			write(1, &tab[str[i]], 1);
		else
			write(1, &str[i], 1);
		i++;
	}
}

void	*ft_print_memory(const void *addr, size_t size)
{
	int				i;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		if (i && i % 16 == 0)
			printf("\n");
		ft_hexaconv((void*)addr + i);
		i += 4;
	}
	return ((void*)addr);
}

int main(void)
{
		int tab[10] = {0, 23, 150, 255, 12, 16,  21, 42};
		ft_print_memory(tab, sizeof(tab));
			return (0);
}
