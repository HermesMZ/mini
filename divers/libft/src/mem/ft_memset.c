/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:18:07 by MZimeris          #+#    #+#             */
/*   Updated: 2025/04/30 23:18:08 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*ptr, int c, size_t n)
{
	char	*cptr;
	size_t	i;

	i = 0;
	cptr = ptr;
	while (i < n)
		cptr[i++] = (unsigned char)c;
	return (ptr);
}
