/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:02:16 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*pad_left(char *str, int total_width, char padding_char,
			int str_len)
{
	char	*padded_str;
	int		padding_len;

	padding_len = total_width - str_len;
	padded_str = malloc(sizeof(char) * (total_width + 1));
	if (!padded_str)
		return (NULL);
	ft_memset(padded_str, padding_char, padding_len);
	ft_memcpy(padded_str + padding_len, str, str_len);
	padded_str[total_width] = '\0';
	free(str);
	return (padded_str);
}

static char	*pad_right(char *str, int total_width, char padding_char,
			int str_len)
{
	char	*padded_str;
	int		padding_len;

	padding_len = total_width - str_len;
	padded_str = malloc(sizeof(char) * (total_width + 1));
	if (!padded_str)
		return (NULL);
	ft_memcpy(padded_str, str, str_len);
	ft_memset(padded_str + str_len, padding_char, padding_len);
	padded_str[total_width] = '\0';
	free(str);
	return (padded_str);
}

char	*apply_padding_width(t_element *element, char *str, char padding_char)
{
	int		str_len;

	if (element->spec == 'c' && str[0] == '\0')
		str_len = 1;
	else
		str_len = ft_strlen(str);
	if (element->width <= str_len)
		return (str);
	if (element->has_minus && (element->spec != 'c' || str[0] != '\0'))
		return (pad_right(str, element->width, padding_char, str_len));
	else
		return (pad_left(str, element->width, padding_char, str_len));
}
