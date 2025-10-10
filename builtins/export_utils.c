#include "../minishell.h"

int	is_valid_identifier(const char *str)
{
	int	idx;

	idx = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[idx] && str[idx] != '=')
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
}

int	extract_key_value(const char *arg, char **key, char **value)
{
	int	sep;

	sep = 0;
	while (arg[sep] && arg[sep] != '=')
		sep++;
	if (!arg[sep])
		return (0);
	*key = ft_substr(arg, 0, sep);
	*value = ft_strdup(arg + sep + 1);
	if (!(*key) || !(*value))
		return (0);
	return (1);
}

void	update_or_add_env(t_minishell *shell, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = ft_strdup("");
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = shell->env_list;
	shell->env_list = new;
}

int	env_has_key(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
