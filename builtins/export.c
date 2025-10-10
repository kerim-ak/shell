#include "../minishell.h"

static void	init_node(t_env **env, t_env **node)
{
	(*node) = malloc(sizeof(t_env));
	(*node)->key = ft_strdup((*env)->key);
	(*node)->value = ft_strdup((*env)->value);
	(*node)->next = NULL;
}

static t_env	*copy_and_sort_env(t_env *env)
{
	t_env	*copy;
	t_env	*node;
	t_env	*iter;

	copy = NULL;
	node = NULL;
	while (env)
	{
		init_node(&env, &node);
		if (!copy || ft_strcmp(node->key, copy->key) < 0)
		{
			node->next = copy;
			copy = node;
		}
		else
		{
			iter = copy;
			while (iter->next && ft_strcmp(node->key, iter->next->key) > 0)
				iter = iter->next;
			node->next = iter->next;
			iter->next = node;
		}
		env = env->next;
	}
	return (copy);
}

static int	print_sorted_env(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;

	sorted = copy_and_sort_env(env);
	tmp = sorted;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env_list(&sorted);
	return (0);
}

static int	export_error(char *argv_index)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argv_index, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
	return (1);
}

int	ft_export(t_minishell *shell, char **argv)
{
	int		i;
	char	*key;
	char	*val;
	int		error;

	if (!argv[1])
		return (print_sorted_env(shell->env_list));
	i = 0;
	error = 0;
	while (argv[++i])
	{
		if (!is_valid_identifier(argv[i]))
			error = export_error(argv[i]);
		else if (!ft_strchr(argv[i], '=')
			&& !env_has_key(shell->env_list, argv[i]))
			update_or_add_env(shell, argv[i], NULL);
		else if (ft_strchr(argv[i], '=')
			&& extract_key_value(argv[i], &key, &val))
		{
			update_or_add_env(shell, key, val);
			free(key);
			free(val);
		}
	}
	return (error);
}
