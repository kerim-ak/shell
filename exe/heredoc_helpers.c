#include "../minishell.h"

static char	*append_valid_var(char *exp, char *line, int *i, t_minishell *shell)
{
	int		j;
	char	*var_name;
	char	*var_value;
	char	*temp;

	j = *i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	var_name = ft_substr(line, *i + 1, j - *i - 1);
	var_value = get_env_value(var_name, shell->env_list);
	if (var_value)
	{
		temp = exp;
		exp = ft_strjoin(exp, var_value);
		free(temp);
	}
	free(var_name);
	*i = j - 1;
	return (exp);
}

static char	*append_invalid_var(char *expanded, char c)
{
	char	*temp;

	temp = expanded;
	expanded = char_append(expanded, c);
	free(temp);
	return (expanded);
}

static char	*append_var_value(char *exp, char *line, int *i, t_minishell *shell)
{
	if (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_')
		return (append_valid_var(exp, line, i, shell));
	return (append_invalid_var(exp, line[*i]));
}

char	*expand_heredoc_line(char *line, t_minishell *shell)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup("");
	if (!expanded)
		return (ft_strdup(line));
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && !isspace(line[i + 1])
			&& line[i + 1] != '$' && line[i + 1] != '\'' && line[i + 1] != '\"')
			expanded = append_var_value(expanded, line, &i, shell);
		else
			expanded = append_invalid_var(expanded, line[i]);
		i++;
	}
	return (expanded);
}

void	cleanup_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
