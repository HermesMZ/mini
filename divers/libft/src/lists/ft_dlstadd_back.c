/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:50:47 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/16 21:16:57 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dblist *dblst, void *content)
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
		dblst->last->next = new_elem;
		new_elem->prev = dblst->last;
		dblst->last = new_elem;
		new_elem->next = dblst->first;
		dblst->first->prev = new_elem;
	}
	dblst->length++;
}
