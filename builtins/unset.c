#include "../minishell.h"

static void	remove_env_key(t_minishell *shell, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = shell->env_list;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				shell->env_list = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(t_minishell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
			printf("minishell: unset: `%s`: not a valid identifier\n", argv[i]);
		else
			remove_env_key(shell, argv[i]);
		i++;
	}
	return (0);
}
