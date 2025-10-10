#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	char			*ret;

	if (ft_strlen(s1) == 0 && ft_strlen(set) == 0)
	{
		ret = ft_calloc(1, 1);
		return (ret);
	}
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (!*s1)
	{
		ret = ft_calloc(1, 1);
		return (ret);
	}
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
