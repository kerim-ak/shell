#include "libft.h"

static int	ft_int_len(int c)
{
	int	len;

	len = 1;
	if (c == -2147483648)
		return (11);
	if (c < 0)
	{
		len++;
		c = -c;
	}
	while (c / 10 != 0)
	{
		len++;
		c /= 10;
	}
	return (len);
}

static char	*ft_numcpy(char *s, int c, int start, int end)
{
	while (end >= start)
	{
		s[end] = c % 10 + 48;
		end--;
		c /= 10;
	}
	return (s);
}

char	*ft_itoa(int c)
{
	int		len;
	char	*ret;

	len = ft_int_len(c);
	ret = malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (c == -2147483648)
	{
		ft_strlcpy(ret, "-2147483648", (len + 1));
		return (ret);
	}
	ret[len] = '\0';
	len--;
	if (c < 0)
	{
		c = -c;
		ft_numcpy(ret, c, 1, len);
		ret[0] = '-';
	}
	else
		ft_numcpy(ret, c, 0, len);
	return (ret);
}
