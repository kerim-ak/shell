#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*temp_src;
	unsigned char	*temp_dst;

	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (dst);
	if ((temp_src < temp_dst) && ((temp_src + len - 1) >= temp_dst))
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			temp_dst[i] = temp_src[i];
			i--;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
