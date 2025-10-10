#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ret;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}
