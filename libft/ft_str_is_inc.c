#include "libft.h"

int ft_str_is_inc(char *big, char *ltl)
{
	int i;
	int j;

	i = 0;
	if (!big || !ltl)
		return (0);
	while (big[i])
	{
		j = 0;
		while (ltl[j] && big[i + j] == ltl[j])
			j++;
		if (ltl[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}
