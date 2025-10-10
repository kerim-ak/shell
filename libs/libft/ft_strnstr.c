#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (ft_strncmp(haystack + i, needle, n_len) == 0 && (i + n_len) <= len)
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
