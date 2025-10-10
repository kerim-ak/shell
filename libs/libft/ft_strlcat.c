#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ini_len;
	size_t	src_len;

	ini_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = ini_len;
	j = 0;
	if (dstsize <= ini_len)
		return (dstsize + src_len);
	while (i < dstsize - 1 && j < src_len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ini_len + src_len);
}
