#include "../minishell.h"

t_redir	*new_redir_node(t_token_type type, char *filename)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->filename = ft_strdup(filename);
	node->heredoc_fd = -1;
	node->next = NULL;
	return (node);
}

void	add_redir_to_back(t_redir **list, t_redir *new_node)
{
	t_redir	*current;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	free_redirs(t_redir **list)
{
	t_redir	*current;
	t_redir	*next;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
	*list = NULL;
}
