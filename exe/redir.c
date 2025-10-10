#include "../minishell.h"

static int	redir_in(t_redir *redir)
{
	int		fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	append(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void	redir_helper(t_redir *redir, int *return_flag)
{
	if (redir->type == TOKEN_REDIR_IN)
		*return_flag = redir_in(redir);
	else if (redir->type == TOKEN_REDIR_OUT)
		*return_flag = redir_out(redir);
	else if (redir->type == TOKEN_APPEND)
		*return_flag = append(redir);
	else if (redir->type == TOKEN_HEREDOC)
	{
		if (redir->heredoc_fd != -1)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
	}
}

int	apply_redirections(t_cmd *cmd, t_minishell *shell)
{
	t_redir	*redir;
	int		return_flag;	

	(void)shell;
	return_flag = 0;
	redir = cmd->redirections;
	while (redir)
	{
		redir_helper(redir, &return_flag);
		if (return_flag)
		{
			if (return_flag == 130)
				return (130);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}
