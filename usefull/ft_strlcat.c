/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:15:29 by MZimeris          #+#    #+#             */
/*   Updated: 2025/08/13 21:16:13 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dsize != 0)
	{
		while (src[i] && dst_len + i < dsize - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	if (dsize <= dst_len)
		return (src_len + dsize);
	return (src_len + dst_len);
}
