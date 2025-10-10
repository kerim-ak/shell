#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	heredoc_wait_child(pid_t pid, int read_fd, void (*old_sigint)(int))
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| WIFSIGNALED(status))
	{
		close(read_fd);
		return (130);
	}
	return (0);
}

static void	fork_error(int pipefd_1, int pipefd_2, void *old_sigint)
{
	perror("fork");
	close(pipefd_1);
	close(pipefd_2);
	signal(SIGINT, old_sigint);
}

static void	assing_helper(t_redir *redir, t_minishell *shell, int res, int p)
{
	if (res == 0)
		redir->heredoc_fd = p;
	if (res == 130)
		shell->last_exit_code = 130;
}

int	process_single_heredoc(t_redir *redir, t_minishell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	void	(*old_sigint)(int);
	int		result;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	g_signal = 1;
	old_sigint = signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		fork_error(pipefd[0], pipefd[1], old_sigint);
	if (pid == -1)
		return (1);
	if (pid == 0)
		return (heredoc_fork_child(pipefd[1], redir->filename, shell), 0);
	close(pipefd[1]);
	result = heredoc_wait_child(pid, pipefd[0], old_sigint);
	assing_helper(redir, shell, result, pipefd[0]);
	return (result);
}
