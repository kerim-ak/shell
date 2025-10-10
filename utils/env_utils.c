#include "../minishell.h"

static t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*p_equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	p_equal = ft_strchr(env_str, '=');
	if (p_equal)
	{
		*p_equal = '\0';
		node->key = ft_strdup(env_str);
		node->value = ft_strdup(p_equal + 1);
		*p_equal = '=';
	}
	else
	{
		node->key = ft_strdup(env_str);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

size_t	env_len(t_env *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

t_env	*initialize_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	head = create_env_node(envp[0]);
	current = head;
	i = 1;
	while (envp[i])
	{
		current->next = create_env_node(envp[i]);
		current = current->next;
		i++;
	}
	return (head);
}

void	free_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*next_node;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next_node = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next_node;
	}
	*env_list = NULL;
}

char	*get_env_value(char *key, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
