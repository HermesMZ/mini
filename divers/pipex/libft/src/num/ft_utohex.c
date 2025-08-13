/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:05:40 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 16:49:14 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digits_count_hex(unsigned long long nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		len = 1;
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

char	*ft_utohex(unsigned long long n)
{
	char				*hex_str;
	size_t				len;
	int					i;
	const char			base[] = "0123456789abcdef";

	len = ft_digits_count_hex(n);
	hex_str = malloc(sizeof(char) * (len + 1));
	if (!hex_str)
		return (NULL);
	hex_str[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		hex_str[i--] = base[n % 16];
		n /= 16;
	}
	return (hex_str);
}
