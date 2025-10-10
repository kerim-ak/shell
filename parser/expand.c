#include "../minishell.h"

static int	expand_helper(char *raw_value, t_quote_state *q_state, int i)
{
	int	flag;

	flag = 0;
	if (*q_state == Q_DEFAULT && raw_value[i] == '\'')
	{
		flag = 1;
		*q_state = Q_IN_SINGLE;
	}
	else if (*q_state == Q_DEFAULT && raw_value[i] == '\"')
	{
		flag = 1;
		*q_state = Q_IN_DOUBLE;
	}
	else if (*q_state == Q_IN_SINGLE && raw_value[i] == '\'')
	{
		flag = 1;
		*q_state = Q_DEFAULT;
	}
	else if (*q_state == Q_IN_DOUBLE && raw_value[i] == '\"')
	{
		flag = 1;
		*q_state = Q_DEFAULT;
	}
	return (flag);
}

static char	*append_and_free(char *result, char *addition)
{
	char	*temp;

	temp = result;
	result = str_append(result, addition);
	free(temp);
	free(addition);
	return (result);
}

static char	*append_char_and_free(char *result, char c)
{
	char	*temp;

	temp = result;
	result = char_append(result, c);
	free(temp);
	return (result);
}

static char	*process_dollar(char *result, char *expanded_part)
{
	if (expanded_part != NULL)
		result = append_and_free(result, expanded_part);
	return (result);
}

char	*expand(char *raw, t_minishell *shell, t_quote_state q_state, int i)
{
	char	*result;
	char	*expanded_part;

	result = ft_strdup("");
	while (raw[++i])
	{
		if (expand_helper(raw, &q_state, i))
			continue ;
		if (raw[i] == '$' && q_state != Q_IN_SINGLE)
		{
			expanded_part = handle_dollar_expansion(&i, raw, shell, q_state);
			result = process_dollar(result, expanded_part);
		}
		else
			result = append_char_and_free(result, raw[i]);
	}
	return (result);
}
