#include "../minishell.h"

static int	process_cmd_heredocs(t_cmd *cmd, t_minishell *shell)
{
	t_redir	*redir;
	int		result;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			result = process_single_heredoc(redir, shell);
			if (result != 0)
				return (result);
		}
		redir = redir->next;
	}
	return (0);
}

int	process_all_heredocs(t_minishell *shell)
{
	t_cmd	*cmd;
	int		result;

	cmd = shell->commands;
	while (cmd)
	{
		result = process_cmd_heredocs(cmd, shell);
		if (result != 0)
		{
			cleanup_heredoc_fds(shell->commands);
			return (result);
		}
		cmd = cmd->next;
	}
	return (0);
}
