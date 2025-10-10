#include "../minishell.h"

static t_cmd	*new_cmd_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (NULL);
	return (node);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		size;
	char	**new_args;

	if (!arg)
		return ;
	size = 0;
	if (cmd->args)
		while (cmd->args[size])
			size++;
	new_args = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return ;
	size = -1;
	if (cmd->args)
	{
		while (cmd->args[++size])
			new_args[size] = cmd->args[size];
	}
	else
		size = 0;
	new_args[size] = ft_strdup(arg);
	new_args[size + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

static void	handle_redir_token(t_cmd *cmd, t_token **token_list)
{
	t_token	*current_token;

	current_token = *token_list;
	if (current_token->next && current_token->next->type == TOKEN_WORD)
	{
		add_redir_to_back(&cmd->redirections, \
			new_redir_node(current_token->type, current_token->next->value));
		*token_list = (*token_list)->next;
	}
}

t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	cmd_head = new_cmd_node();
	current_cmd = cmd_head;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg_to_cmd(current_cmd, tokens->value);
		else if (tokens->type >= TOKEN_REDIR_IN \
			&& tokens->type <= TOKEN_HEREDOC)
			handle_redir_token(current_cmd, &tokens);
		else if (tokens->type == TOKEN_PIPE)
		{
			current_cmd->next = new_cmd_node();
			current_cmd = current_cmd->next;
		}
		tokens = tokens->next;
	}
	return (cmd_head);
}

void	free_commands(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!cmds || !*cmds)
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		if (current->redirections)
			free_redirs(&current->redirections);
		free(current);
		current = next;
	}
	*cmds = NULL;
}
