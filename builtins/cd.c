#include "../minishell.h"

static int	cd_helper(char *path, char *oldpwd)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	perror("");
	free(oldpwd);
	return (1);
}

static void	end_cd(t_minishell *shell, char *path, char *oldpwd)
{
	update_or_add_env(shell, "PWD", path);
	update_or_add_env(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	free(path);
}

int	ft_cd(char **argv, t_minishell *shell)
{
	char	*path;
	char	*oldpwd;

	if (argv[1] && argv[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	if (argv[1] && argv[2])
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			free(oldpwd);
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path))
		return (cd_helper(path, oldpwd));
	path = getcwd(NULL, 0);
	end_cd(shell, path, oldpwd);
	return (0);
}
