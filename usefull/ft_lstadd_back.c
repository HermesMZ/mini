#include "../includes/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp_lst;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp_lst = *lst;
	while (tmp_lst -> next != NULL)
		tmp_lst = tmp_lst -> next;
	new -> prev = tmp_lst;
	tmp_lst -> next = new;
}
