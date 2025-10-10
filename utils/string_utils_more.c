#include "../minishell.h"

char	*str_append(char *base, char *to_append)
{
	char	*new_str;

	new_str = ft_strjoin(base, to_append);
	return (new_str);
}

char	*char_append(char *base, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (str_append(base, str));
}

void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}
