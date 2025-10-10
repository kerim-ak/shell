#include "../minishell.h"

static void	update_exit_status_on_exit(int status, int i, int cmd_count,
		t_minishell *shell)
{
	if (WEXITSTATUS(status) == 130)
	{
		shell->last_exit_code = 130;
		return ;
	}
	if (i == cmd_count - 1)
		shell->last_exit_code = WEXITSTATUS(status);
}

static void	update_exit_status_on_signal(int status, int i, int cmd_count,
		t_minishell *shell)
{
	if (i == cmd_count - 1)
	{
		if (WTERMSIG(status) == SIGINT)
			shell->last_exit_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			shell->last_exit_code = 131;
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}	
		else
			shell->last_exit_code = 128 + WTERMSIG(status);
	}
}

void	wait_all_children(pid_t *pids, int cmd_count, t_minishell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			update_exit_status_on_exit(status, i, cmd_count, shell);
		else if (WIFSIGNALED(status))
			update_exit_status_on_signal(status, i, cmd_count, shell);
		i++;
	}
}
