#include "../minishell.h"

static int	get_word_token_len(const char *s)
{
	int				i;
	t_quote_state	q_state;

	i = 0;
	q_state = Q_DEFAULT;
	while (s[i])
	{
		if (q_state == Q_DEFAULT && (s[i] == '\'' || s[i] == '\"'))
		{
			if (s[i] == '\'')
				q_state = Q_IN_SINGLE;
			else
				q_state = Q_IN_DOUBLE;
		}
		else if (q_state == Q_IN_SINGLE && s[i] == '\'')
			q_state = Q_DEFAULT;
		else if (q_state == Q_IN_DOUBLE && s[i] == '\"')
			q_state = Q_DEFAULT;
		if (q_state == Q_DEFAULT && (s[i] == ' ' || s[i] == '\t' || \
			s[i] == '|' || s[i] == '<' || s[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

static int	handle_metachar(const char *line, t_token **token_list)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		return (tok_add_back(token_list, tok_new(">>", TOKEN_APPEND)), 2);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (tok_add_back(token_list, tok_new("<<", TOKEN_HEREDOC)), 2);
	if (*line == '>')
		return (tok_add_back(token_list, tok_new(">", TOKEN_REDIR_OUT)), 1);
	if (*line == '<')
		return (tok_add_back(token_list, tok_new("<", TOKEN_REDIR_IN)), 1);
	if (*line == '|')
		return (tok_add_back(token_list, tok_new("|", TOKEN_PIPE)), 1);
	return (0);
}

static int	process_word_token(t_token **head, const char **line)
{
	char	*value;
	int		len;

	len = get_word_token_len(*line);
	value = ft_substr(*line, 0, len);
	if (!value)
	{
		tok_clear(head);
		return (0);
	}
	tok_add_back(head, tok_new(value, TOKEN_WORD));
	free(value);
	*line += len;
	return (1);
}

t_token	*tokenizer(const char *line)
{
	t_token	*head;
	int		len;

	head = NULL;
	while (line && *line)
	{
		if (*line == ' ' || *line == '\t')
		{
			line++;
			continue ;
		}
		len = handle_metachar(line, &head);
		if (len > 0)
		{
			line += len;
			continue ;
		}
		if (!process_word_token(&head, &line))
			return (NULL);
	}
	return (head);
}
