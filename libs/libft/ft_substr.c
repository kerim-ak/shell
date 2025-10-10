#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	s_len;

	s_len = (unsigned int)ft_strlen(s);
	i = 0;
	if (start >= s_len)
	{
		sub = ft_calloc (1, 1);
		return (sub);
	}
	if ((s_len - start) < len)
		sub = malloc((s_len - start + 1) * sizeof(char));
	else
		sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len && s[start] != '\0' && start < s_len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
