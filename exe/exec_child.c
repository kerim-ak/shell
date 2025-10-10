#include "../minishell.h"

static void	free_child_shell_state(t_minishell *shell, pid_t *pids)
{
	free_commands(&shell->commands);
	free_env_list(&shell->env_list);
	free(pids);
}

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	handle_redirections(t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	int	redir_status;

	redir_status = apply_redirections(cmd, shell);
	if (redir_status == 130)
	{
		free_child_shell_state(shell, pids);
		exit(130);
	}
	if (redir_status != 0)
	{
		free_child_shell_state(shell, pids);
		exit(1);
	}
}

static void	cleanup_empty_args(t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	int		i;
	char	*temp;

	temp = NULL;
	while (cmd->args && cmd->args[0] && ft_strlen(cmd->args[0]) == 0)
	{
		i = 0;
		temp = cmd->args[0];
		while (cmd->args[i])
		{
			cmd->args[i] = cmd->args[i + 1];
			i++;
		}
		free(temp);
		if (!cmd->args[0])
		{
			free_child_shell_state(shell, pids);
			exit(0);
		}
	}
}

void	execute_child(t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	char	*cmd_path;
	char	**env_array;

	setup_child_signals();
	handle_redirections(shell, cmd, pids);
	exec_builtin_or_continue(shell, cmd, pids);
	cleanup_empty_args(shell, cmd, pids);
	cmd_path = resolve_command_path(shell, cmd, pids);
	env_array = env_list_to_array(shell->env_list);
	execve(cmd_path, cmd->args, env_array);
	free_str_array(env_array);
	handle_execve_error(cmd_path, cmd->args[0], shell, pids);
}
