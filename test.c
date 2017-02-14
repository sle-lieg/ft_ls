#include <stdio.h>
#include "libft/libft.h"

int main(void)
{
	char *str;

	str = (char *)malloc(sizeof(*str) * 4096);
	str = "bonjourqwertyuiop";

	printf("%s\n", str);
	ft_bzero(str, 4095);
	printf("%s\n", str);
	return (0);
}
