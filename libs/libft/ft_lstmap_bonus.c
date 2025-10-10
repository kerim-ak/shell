#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*temp_list;
	void	*temp;

	ret = NULL;
	while (lst)
	{
		temp = f(lst->content);
		temp_list = ft_lstnew(temp);
		if (!temp_list)
		{
			ft_lstclear(&ret, *del);
			free(temp_list);
			free(ret);
			free(temp);
			return (NULL);
		}
		ft_lstadd_back(&ret, temp_list);
		lst = lst->next;
	}
	return (ret);
}
