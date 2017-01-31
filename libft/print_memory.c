#include <unistd.h>
#include <stdio.h>

void	print_line(const void *addr, size_t size)
{
	unsigned char	c;
	size_t			i;

	i = 0;
	while (i < size)
	{
		c = *((unsigned char *)(addr + i));
		if (c < 33 || c > 126)
			write(1, ".", 1);
		else
			write(1, &c, 1);
		++i;
	}
}

void	print_hex(const unsigned char c)
{
	char	r;

	r = (c & 0xF0) >> 4;
	if (r < 10)
		r += '0';
	else
		r += 'a' - 10;
	write(1, &r, 1);
	r = c & 0x0F;
	if (r < 10)
		r += '0';
	else
		r += 'a' - 10;
	write(1, &r, 1);

}

void	print_memory(const void *addr, size_t size)
{
	size_t			i;
	size_t			j;
	size_t			k;
	unsigned char	c;

	i = 0;
	j = 0;
	while (i < size)
	{
		print_hex(*(unsigned char *)(addr + i++));
		if (i % 2 == 0)
			write(1, " ", 1);
		if (i % 16 == 0)
		{
			print_line(addr + j, 16);
			j = i;
			write(1, "\n", 1);
		}
	}
	k = i;
	while (i % 16 != 0)
	{
		if (i % 2 == 0)
			write(1, " ", 1);
		write(1, "  ", 2);
		++i;
	}
	print_line(addr + j, i - k);
	write(1, "\n", 1);
}

int	main(void)
{
	int	tab[10] = {0, 23, 150, 255,
		12, 16,  21, 42};

	print_memory(tab, sizeof(tab));
	return (0);
}
