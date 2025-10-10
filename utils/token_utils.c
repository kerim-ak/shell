#include "../minishell.h"

static char	*tok_strdup(const char *s)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	j = -1;
	while (s[i])
		++i;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	while (++j < i)
		dup[j] = s[j];
	dup[i] = '\0';
	return (dup);
}

t_token	*tok_new(char *text, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = tok_strdup(text);
	if (!node->value)
		return (free(node), NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	tok_add_back(t_token **lst, t_token *new_token)
{
	t_token	*tmp;

	if (!lst || !new_token)
		return ;
	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	tok_clear(t_token **lst)
{
	t_token	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
