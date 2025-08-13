/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:05:28 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/16 21:16:45 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dblist *dblst, void *content)
{
	t_elem	*new_elem;

	if (!dblst)
		return ;
	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return ;
	new_elem->content = content;
	if (dblst->length == 0)
	{
		dblst->first = new_elem;
		dblst->last = new_elem;
		new_elem->next = new_elem;
		new_elem->prev = new_elem;
	}
	else
	{
		dblst->first->prev = new_elem;
		new_elem->next = dblst->first;
		dblst->first = new_elem;
		new_elem->prev = dblst->last;
		dblst->last->next = new_elem;
	}
	dblst->length++;
}
