/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:25:08 by zoum              #+#    #+#             */
/*   Updated: 2025/07/16 22:27:31 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

unsigned int	ft_hextoul(const char *str)
{
	unsigned int	result;
	int				digit_val;

	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (*str)
	{
		digit_val = hex_char_to_int(*str);
		if (digit_val == -1)
			break ;
		result = result * 16 + digit_val;
		str++;
	}
	return (result);
}

int	ft_hextoi(const char *str)
{
	return ((int)ft_hextoul(str));
}
