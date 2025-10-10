#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s1_temp;
	const char	*s2_temp;

	i = 0;
	s1_temp = (const char *)s1;
	s2_temp = (const char *)s2;
	while (i < n)
	{
		if ((unsigned char)*s1_temp != (unsigned char)*s2_temp)
			return ((unsigned char)*s1_temp - (unsigned char)*s2_temp);
		s1_temp++;
		s2_temp++;
		i++;
	}
	return (0);
}
