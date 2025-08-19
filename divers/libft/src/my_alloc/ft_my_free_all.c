/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_free_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:58:47 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 16:33:35 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_my_alloc.h"

void	*ft_my_free_all(t_lalloc *lalloc)
{
	t_my_malloc	*current;
	t_my_malloc	*next;
	void		*ptr;
	t_lalloc	*allocator_to_free;

	if (!lalloc)
		return (NULL);
	current = lalloc->head;
	allocator_to_free = NULL;
	while (current)
	{
		next = current->next;
		ptr = current->ptr;
		if (ptr == lalloc)
			allocator_to_free = lalloc;
		else
			free(ptr);
		free(current);
		current = next;
	}
	if (allocator_to_free)
		free(allocator_to_free);
	return (NULL);
}
