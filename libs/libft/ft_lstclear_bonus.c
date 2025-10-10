#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
	lst = NULL;
}
