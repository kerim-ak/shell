#include "minishell.h"

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal == 1)
		{
			write(1, "\n", 1);
			return ;
		}
		else if (g_signal == 2)
		{
			write(1, "\n", 1);
			return ;
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	init_shell(t_minishell *shell, char **envp)
{
	shell->env_list = initialize_env(envp);
	shell->last_exit_code = 0;
	shell->should_exit = 0;
	shell->commands = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	int				status;
	t_minishell		shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell(&shell, envp);
	status = main_loop(&shell);
	free_env_list(&shell.env_list);
	if (!status)
		return (0);
	return (shell.last_exit_code);
}
