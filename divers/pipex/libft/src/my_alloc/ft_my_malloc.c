/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:35:07 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 12:53:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_my_alloc.h"

void	*ft_my_malloc(t_lalloc *lalloc, size_t size)
{
	t_my_malloc	*new;

	new = malloc(sizeof(t_my_malloc));
	if (!new)
		return (NULL);
	new->size = size;
	new->ptr = malloc(size);
	if (!new->ptr)
	{
		free(new);
		return (NULL);
	}
	new->next = lalloc->head;
	lalloc->head = new;
	lalloc->total_allocated += size;
	return (new->ptr);
}
