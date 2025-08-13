/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:09:23 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:50:39 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_string;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	final_string = (char *)malloc(sizeof(char) * (size + 1));
	if (!final_string)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		final_string[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		final_string[i + j] = s2[j];
		j++;
	}
	final_string[i + j] = '\0';
	return (final_string);
}
