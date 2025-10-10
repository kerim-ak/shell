#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char	**free_array_and_return_null(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	*create_env_string(t_env *env_node)
{
	char	*temp;
	char	*final_str;

	if (env_node->value == NULL)
		return (ft_strdup(env_node->key));
	temp = ft_strjoin(env_node->key, "=");
	if (!temp)
		return (NULL);
	final_str = ft_strjoin(temp, env_node->value);
	free(temp);
	return (final_str);
}

static int	fill_array_from_list(char **array, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		array[i] = create_env_string(env);
		if (!array[i])
		{
			free_array_and_return_null(array, i);
			return (0);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**env_list_to_array(t_env *env)
{
	size_t	len;
	char	**array;

	len = env_len(env);
	if (!len)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	if (!fill_array_from_list(array, env))
		return (NULL);
	return (array);
}
