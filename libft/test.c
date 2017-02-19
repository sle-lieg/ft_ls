#include "stdio.h"
#include "libft.h"

int main()
{
	int nb = 0;

	while (nb < 100)
	{  
		printf("%s\n", ft_itoa(nb));
		nb++;
	}	
return (0);
}
