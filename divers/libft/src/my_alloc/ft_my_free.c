/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:56:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 12:56:52 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_my_alloc.h"

void	ft_my_free(t_lalloc *lalloc, void *ptr)
{
	t_my_malloc	*current;
	t_my_malloc	*prev;

	if (!lalloc || !ptr)
		return ;
	current = lalloc->head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				lalloc->head = current->next;
			lalloc->total_freed += current->size;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
