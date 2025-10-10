#include "minishell.h"

static void	handle_line(char *line, t_minishell *shell)
{
	if (*line)
		add_history(line);
	if (parser(shell, line) == 0 && shell->commands)
	{
		if (process_all_heredocs(shell) == 0)
			executor(shell, -1);
		else
			shell->last_exit_code = 130;
	}
	cleanup_heredoc_fds(shell->commands);
	free_commands(&shell->commands);
}

static void	assign_line(char **line, char c)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin_char(*line, c);
	free(temp);
}

static char	*read_line_non_interactive(char c)
{
	char	*line;
	int		read_return;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		read_return = read(STDIN_FILENO, &c, 1);
		if (read_return <= 0)
			break ;
		if (c == '\n')
			break ;
		assign_line(&line, c);
		if (!line)
			return (NULL);
	}
	if (read_return <= 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main_loop(t_minishell *shell)
{
	char	*line;
	char	c;

	c = 0;
	while (1)
	{
		shell->commands = NULL;
		if (isatty(STDIN_FILENO))
			line = readline("minishell$ ");
		else
			line = read_line_non_interactive(c);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			return (0);
		}
		handle_line(line, shell);
		free(line);
		if (shell->should_exit)
			break ;
	}
	return (1);
}
