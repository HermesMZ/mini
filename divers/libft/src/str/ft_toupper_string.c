/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:48:09 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/20 16:48:12 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_toupper_string(const char *str)
{
	size_t	i;
	char	*upper_str;

	if (!str)
		return (NULL);
	upper_str = ft_strdup(str);
	if (!upper_str)
		return (NULL);
	i = 0;
	while (upper_str[i])
	{
		if (upper_str[i] >= 'a' && upper_str[i] <= 'z')
			upper_str[i] -= 32;
		i++;
	}
	return (upper_str);
}
