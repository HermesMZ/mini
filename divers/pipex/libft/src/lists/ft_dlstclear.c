/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:54:48 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/14 16:23:44 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dblist **p_lst, void (*del)(void*))
{
	t_elem	*current;
	t_elem	*next_elem;

	if (!p_lst || !*p_lst || !del)
		return ;
	if ((*p_lst)->length == 0)
	{
		free(*p_lst);
		*p_lst = NULL;
		return ;
	}
	(*p_lst)->last->next = NULL;
	current = (*p_lst)->first;
	while (current)
	{
		next_elem = current->next;
		ft_dlstdelone(current, del);
		current = next_elem;
	}
	free(*p_lst);
	*p_lst = NULL;
}
