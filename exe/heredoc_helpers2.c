#include "../minishell.h"

static void	heredoc_sigint_child(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_signal = 4;
	close(STDIN_FILENO);
}

static void	free_child_shell_state(t_minishell *shell)
{
	free_commands(&shell->commands);
	free_env_list(&shell->env_list);
}

static int	process_heredoc_line(char *delimiter, t_minishell *shell, int fd)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	if (g_signal == 4)
		return (-1);
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (2);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	expanded_line = expand_heredoc_line(line, shell);
	ft_putendl_fd(expanded_line, fd);
	free(expanded_line);
	free(line);
	return (0);
}

static int	write_heredoc_content(int fd, char *delimiter, t_minishell *shell)
{
	int	status;

	signal(SIGINT, heredoc_sigint_child);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		status = process_heredoc_line(delimiter, shell, fd);
		if (status == 1 || status == 2)
			break ;
		else if (status == -1)
		{
			free_child_shell_state(shell);
			exit(130);
		}
	}
	free_child_shell_state(shell);
	return (0);
}

int	heredoc_fork_child(int write_fd, char *delim, t_minishell *shell)
{
	write_heredoc_content(write_fd, delim, shell);
	close(write_fd);
	exit(0);
}
