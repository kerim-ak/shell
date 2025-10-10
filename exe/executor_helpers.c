#include "../minishell.h"

static void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	executor_builtin(t_cmd *cmd, t_minishell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
	int	redir_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_status = apply_redirections(cmd, shell);
	if (redir_status != 0)
	{
		restore_stdio(saved_stdin, saved_stdout);
		if (redir_status == 130)
		{
			shell->last_exit_code = 130;
			return (130);
		}
		return (1);
	}
	status = exec_builtin(cmd->args, shell);
	restore_stdio(saved_stdin, saved_stdout);
	return (status);
}

int	is_single_builtin(t_cmd *cmd)
{
	return (cmd && !cmd->next && builtin_check(cmd->args));
}

pid_t	*init_child_pid_array(int cmd_count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		perror("malloc");
	return (pids);
}

void	if_exec(int pid, t_minishell *shell, t_cmd *cmd, pid_t *pids)
{
	if (pid == 0)
		execute_child(shell, cmd, pids);
}
