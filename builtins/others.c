#include "../minishell.h"

static int	num_check(char *str)
{
	if (!str || !(*str))
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_exit(char **argv, t_minishell *shell)
{
	int	status;

	status = 0;
	printf("exit\n");
	if (argv[1])
	{
		if (!num_check(argv[1]))
		{
			write(2, "minishell: exit: numeric argument required\n", 42);
			shell->should_exit = 1;
			return (2);
		}
		else if (argv[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		status = ft_atoi(argv[1]);
	}
	shell->should_exit = 1;
	return (status);
}

int	ft_env(char **argv, t_minishell *shell)
{
	t_env	*cur;

	if (argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (127);
	}
	cur = shell->env_list;
	while (cur)
	{
		if (cur->key)
		{
			if (cur->value)
				printf("%s=%s\n", cur->key, cur->value);
		}
		cur = cur->next;
	}
	return (0);
}
