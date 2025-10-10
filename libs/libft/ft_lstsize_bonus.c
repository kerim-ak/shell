#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	if (temp == NULL)
		return (0);
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (i + 1);
}
