#include "../minishell.h"

static void	free_child_shell_state(t_minishell *shell, pid_t *pids)
{
	free_commands(&shell->commands);
	free_env_list(&shell->env_list);
	free(pids);
}

int	builtin_check(char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "echo", 5))
		return (1);
	if (!ft_strncmp(argv[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(argv[0], "cd", 3))
		return (1);
	if (!ft_strncmp(argv[0], "exit", 5))
		return (1);
	if (!ft_strncmp(argv[0], "env", 4))
		return (1);
	if (!ft_strncmp(argv[0], "export", 7))
		return (1);
	if (!ft_strncmp(argv[0], "unset", 6))
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_minishell *shell)
{
	int	status;

	if (!ft_strncmp(argv[0], "echo", 5))
		return (ft_echo(argv));
	if (!ft_strncmp(argv[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(argv[0], "cd", 3))
		return (ft_cd(argv, shell));
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		status = ft_exit(argv, shell);
		return (status);
	}
	if (!ft_strncmp(argv[0], "env", 4))
		return (ft_env(argv, shell));
	if (!ft_strncmp(argv[0], "export", 7))
		return (ft_export(shell, argv));
	if (!ft_strncmp(argv[0], "unset", 6))
		return (ft_unset(shell, argv));
	return (1);
}

void	exec_builtin_or_continue(t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	int	exit_code;

	if (!cmd->args || !cmd->args[0])
	{
		free_child_shell_state(shell, pids);
		exit(0);
	}
	if (builtin_check(cmd->args))
	{
		exit_code = exec_builtin(cmd->args, shell);
		free_child_shell_state(shell, pids);
		exit(exit_code);
	}
}
