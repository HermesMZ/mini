/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:18:31 by mzimeris          #+#    #+#             */
/*   Updated: 2025/04/28 13:23:31 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_charset(s1[start], set))
		start++;
	while (start < end && is_charset(s1[end - 1], set))
		end--;
	tmp = (char *)malloc((sizeof(char) * (end - start + 1)));
	if (!tmp)
		return (NULL);
	i = 0;
	while (start < end)
		tmp[i++] = s1[start++];
	tmp[i] = '\0';
	return (tmp);
}
