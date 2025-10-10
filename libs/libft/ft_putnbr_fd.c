#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = 0;
	if (n == -2147483648)
	{
		ft_putnbr_fd(-214748364, fd);
		ft_putnbr_fd(8, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + 48;
		ft_putchar_fd(c, fd);
	}
}
