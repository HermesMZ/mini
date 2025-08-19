#include "../includes/minishell.h"

void	ft_tokenlstclear(t_token **lst)
{
	t_token	*tmp;
	t_token	*next;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
