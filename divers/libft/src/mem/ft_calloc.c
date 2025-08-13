/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:34:59 by MZimeris          #+#    #+#             */
/*   Updated: 2025/04/30 02:35:04 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*ptr, int c, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tmp;
	size_t			total_size;

	if (!nmemb || !size)
	{
		tmp = malloc(1);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	if (size > 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	total_size = nmemb * size;
	tmp = malloc(total_size);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, total_size);
	return (tmp);
}
