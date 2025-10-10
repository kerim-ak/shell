#include "../minishell.h"

void	free_child_shell_state(t_minishell *shell, pid_t *pids)
{
	free_commands(&shell->commands);
	free_env_list(&shell->env_list);
	free(pids);
}

char	*resolve_command_path(t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	char		*cmd_path;
	struct stat	st;

	cmd_path = find_command_path(cmd->args[0], shell->env_list);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_child_shell_state(shell, pids);
		exit(127);
	}
	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(cmd_path);
		free_child_shell_state(shell, pids);
		exit(126);
	}
	return (cmd_path);
}

void	handle_execve_error(char *cmdp, char *cmd, t_minishell *sh, pid_t *ps)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_child_shell_state(sh, ps);
		free(cmdp);
		exit(126);
	}
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_child_shell_state(sh, ps);
		free(cmdp);
		exit(127);
	}
	perror("execve");
	free(cmdp);
	free_child_shell_state(sh, ps);
	exit(126);
}
