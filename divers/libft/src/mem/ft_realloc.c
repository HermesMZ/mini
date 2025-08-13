/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:51:13 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/14 22:31:04 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*tmp;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(tmp, ptr, size);
		free(ptr);
	}
	return (tmp);
}
