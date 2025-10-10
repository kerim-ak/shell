#include "../minishell.h"

static void	end_exec(int **pipes, int cmd_c, pid_t *pids, t_minishell *shell)
{
	close_all_pipes(pipes, cmd_c);
	wait_all_children(pids, cmd_c, shell);
	free_pipes(pipes, cmd_c);
	free(pids);
	g_signal = 0;
}

static void	setup_pipe_helper(int i, int cmd_count, int **pipes)
{
	setup_child_pipes(i, cmd_count, pipes);
	close_all_pipes(pipes, cmd_count);
	free_pipes(pipes, cmd_count);
}

static void	set_exit_code(t_cmd *cmd, t_minishell *shell)
{
	if (is_single_builtin(cmd))
		shell->last_exit_code = executor_builtin(cmd, shell);
}

static void	if_pipe(int pid, int i, int cmd_count, int **pipes)
{
	if (pid == 0)
		setup_pipe_helper(i, cmd_count, pipes);
}

void	executor(t_minishell *shell, int i)
{
	t_cmd	*cmd;
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;

	cmd = shell->commands;
	cmd_count = count_commands(cmd);
	set_exit_code(cmd, shell);
	if (is_single_builtin(cmd))
		return ;
	g_signal = 2;
	pipes = create_pipes(cmd_count);
	pids = init_child_pid_array(cmd_count);
	if (!pids)
		g_signal = 0;
	if (!pids)
		return ;
	while (cmd && ++i > -1)
	{
		pids[i] = fork();
		if_pipe(pids[i], i, cmd_count, pipes);
		if_exec(pids[i], shell, cmd, pids);
		cmd = cmd->next;
	}
	end_exec(pipes, cmd_count, pids, shell);
}
