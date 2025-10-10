#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ret = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (!ret)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
