#include "../minishell.h"

static char	*expand_env_var(int *i, char *raw, t_minishell *shell)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = *i + 1;
	if (!ft_isalpha(raw[j]) && raw[j] != '_')
		return (NULL);
	j++;
	while (ft_isalnum(raw[j]) || raw[j] == '_')
		j++;
	var_name = ft_substr(raw, *i + 1, j - (*i + 1));
	var_value = get_env_value(var_name, shell->env_list);
	free(var_name);
	*i = j - 1;
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

char	*handle_dollar_expansion(int *i, char *raw, t_minishell *shell,
	t_quote_state q_state)
{
	char	next_char;

	if (!raw[*i + 1])
		return (ft_strdup("$"));
	next_char = raw[*i + 1];
	if (next_char == '?')
	{
		*i += 1;
		return (ft_itoa(shell->last_exit_code));
	}
	if (ft_isalpha(next_char) || next_char == '_')
		return (expand_env_var(i, raw, shell));
	if (q_state == Q_DEFAULT && (next_char == '"' || next_char == '\''))
		return (ft_strdup(""));
	if (ft_isdigit(next_char))
	{
		*i += 1;
		return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}
