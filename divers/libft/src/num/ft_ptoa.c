/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:38 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/17 20:04:41 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptoa(unsigned long long ptr)
{
	char	*hex_str;
	char	*result;

	if (ptr == 0)
		return (ft_strdup("(nil)"));
	hex_str = ft_utohex(ptr);
	if (!hex_str)
		return (NULL);
	result = ft_strjoin("0x", hex_str);
	free(hex_str);
	return (result);
}
