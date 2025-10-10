#include "libft.h"

static int	ft_counter(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	if (s[0] != c && s[0] != '\0')
		return (count + 1);
	return (count);
}

static char	*ft_word_picker(const char *s, char c)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	i = 0;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static void	ft_free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	char	*temp;
	int		k;

	k = 0;
	list = (char **)malloc((ft_counter(s, c) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			temp = ft_word_picker(s, c);
			list[k++] = temp;
			if (!temp)
			{
				ft_free_list(list);
				return (NULL);
			}
			s += (int)ft_strlen(temp) - 1;
		}
		s++;
	}
	list[k] = NULL;
	return (list);
}
