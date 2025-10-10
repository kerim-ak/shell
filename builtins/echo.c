#include "../minishell.h"

static int	echo_n_check(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	ft_echo(char **argv)
{
	int	line;
	int	i;

	line = 1;
	i = 1;
	while (argv[i] && echo_n_check(argv[i]))
	{
		line = 0;
		i++;
	}
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
