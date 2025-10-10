#include "../minishell.h"

static int	has_unclosed_quotes(const char *line)
{
	t_quote_state	q_state;
	int				i;

	q_state = Q_DEFAULT;
	i = 0;
	while (line[i])
	{
		if (q_state == Q_DEFAULT && line[i] == '\'')
			q_state = Q_IN_SINGLE;
		else if (q_state == Q_DEFAULT && line[i] == '\"')
			q_state = Q_IN_DOUBLE;
		else if (q_state == Q_IN_SINGLE && line[i] == '\'')
			q_state = Q_DEFAULT;
		else if (q_state == Q_IN_DOUBLE && line[i] == '\"')
			q_state = Q_DEFAULT;
		i++;
	}
	if (q_state != Q_DEFAULT)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

static int	is_invalid_operator_sequence(t_token *token)
{
	if (token->type >= TOKEN_PIPE && token->type <= TOKEN_HEREDOC)
	{
		if (token->next == NULL)
		{
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `newline'\n", 2);
			return (1);
		}
		if (token->type == TOKEN_PIPE && token->next->type == TOKEN_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token `|'\n", 2);
			return (1);
		}
		if (token->type != TOKEN_PIPE && token->next->type >= TOKEN_PIPE
			&& token->next->type <= TOKEN_HEREDOC)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->next->value, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_operator_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (current)
	{
		if (current->type >= TOKEN_PIPE && current->type <= TOKEN_HEREDOC)
		{
			if (is_invalid_operator_sequence(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	parser(t_minishell *shell_data, char *line)
{
	t_token	*tokens;
	t_token	*expanded_tokens;

	if (has_unclosed_quotes(line))
	{
		shell_data->last_exit_code = 2;
		return (1);
	}
	tokens = tokenizer(line);
	if (!tokens)
		return (0);
	if (check_operator_syntax(tokens))
	{
		shell_data->last_exit_code = 2;
		tok_clear(&tokens);
		return (1);
	}
	expanded_tokens = expander(tokens, shell_data);
	tok_clear(&tokens);
	shell_data->commands = build_commands(expanded_tokens);
	tok_clear(&expanded_tokens);
	return (0);
}
