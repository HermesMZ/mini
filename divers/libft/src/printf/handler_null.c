/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 02:27:37 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/23 02:27:39 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_padding(int width, char pad_char)
{
	int	written;
	int	i;

	written = 0;
	i = 0;
	while (i < width)
	{
		written += write(1, &pad_char, 1);
		i++;
	}
	return (written);
}

int	handle_null_char_with_padding(t_element *element)
{
	int	printed;
	int	width;

	printed = 0;
	if (element->width > 1)
		width = element->width;
	else
		width = 1;
	if (!has_option(element))
		return (write(1, "\0", 1));
	else if (element->has_minus)
	{
		printed += write(1, "\0", 1);
		printed += write_padding(width - 1, ' ');
	}
	else
	{
		printed += write_padding(width - 1, ' ');
		printed += write(1, "\0", 1);
	}
	return (printed);
}

// printf("|%s|\n", NULL);      // affiche |(null)|
// printf("|%.3s|\n", NULL);    // affiche || (rien entre les pipes)
// printf("|%5.3s|\n", NULL);   // affiche |     | (5 espaces, largeur=5)

char	*handle_null_string(t_element *element, char *str)
{
	char	*truncated_null;
	int		len;

	len = (int)ft_strlen("(null)");
	if (element->precision < len && element->precision != -1)
	{
		free(str);
		return (ft_strdup(""));
	}
	else if (element->precision > 0 && element->precision < len)
	{
		truncated_null = malloc(element->precision + 1);
		if (!truncated_null)
			return (NULL);
		ft_memcpy(truncated_null, "(null)", element->precision);
		truncated_null[element->precision] = '\0';
		free(str);
		return (truncated_null);
	}
	free(str);
	return (ft_strdup("(null)"));
}
