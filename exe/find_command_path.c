#include "../minishell.h"

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = str_append(dir, "/");
	full_path = str_append(temp, cmd);
	free(temp);
	return (full_path);
}

static char	*cmd_path_helper(char **paths, char *cmd, int i)
{
	char	*full_path;

	full_path = build_cmd_path(paths[i], cmd);
	if (access(full_path, X_OK) == 0)
	{
		free_str_array(paths);
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env_list)
{
	char	*path_value;
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_value = get_env_value("PATH", env_list);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = cmd_path_helper(paths, cmd, i);
		if (full_path)
			return (full_path);
	}
	free_str_array(paths);
	return (NULL);
}
