#include "../minishell.h"

static int	check_was_quoted(char *value)
{
	if (ft_strchr(value, '"') != NULL)
		return (1);
	if (ft_strchr(value, '\'') != NULL)
		return (1);
	return (0);
}

static void	create_and_add_split_tokens(t_token **list, char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		tok_add_back(list, tok_new(split[i], TOKEN_WORD));
		i++;
	}
}

static void	handle_expandable_word(t_token **new_list, t_token *token,
	t_minishell *shell)
{
	int		was_quoted;
	char	*expanded_value;
	char	**split;

	was_quoted = check_was_quoted(token->value);
	expanded_value = expand(token->value, shell, Q_DEFAULT, -1);
	if (expanded_value[0] == '\0' && !was_quoted)
	{
		free(expanded_value);
		return ;
	}
	if (!was_quoted && ft_strchr(expanded_value, ' '))
	{
		split = ft_split(expanded_value, ' ');
		create_and_add_split_tokens(new_list, split);
		free_str_array(split);
		free(expanded_value);
	}
	else
	{
		tok_add_back(new_list, tok_new(expanded_value, TOKEN_WORD));
		free(expanded_value);
	}
}

static void	handle_non_expandable_token(t_token **new_list, t_token *token)
{
	tok_add_back(new_list, tok_new(token->value, token->type));
}

t_token	*expander(t_token *tokens, t_minishell *shell)
{
	t_token	*current;
	t_token	*new_list_head;
	t_token	*prev;

	new_list_head = NULL;
	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type != TOKEN_WORD
			|| (prev && prev->type == TOKEN_HEREDOC))
			handle_non_expandable_token(&new_list_head, current);
		else
			handle_expandable_word(&new_list_head, current, shell);
		prev = current;
		current = current->next;
	}
	return (new_list_head);
}
