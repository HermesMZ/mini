/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:22:53 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_element *element)
{
	unsigned char	char_to_print;
	char			*char_str;
	int				printed;

	char_to_print = (unsigned char)(long)element->content;
	if (element->spec == '%')
		element->width = 0;
	char_str = malloc(sizeof(char) * 2);
	if (!char_str)
		return (-1);
	char_str[0] = char_to_print;
	char_str[1] = '\0';
	element->content = (void *)char_str;
	printed = handle_str(element);
	return (printed);
}

int	handle_number(t_element *element)
{
	long long	value;
	char		*str_value;
	int			printed;

	value = (long long)element->content;
	str_value = ft_itoa_ll(value);
	if (!str_value)
		return (-1);
	element->content = (void *)str_value;
	printed = handle_str(element);
	return (printed);
}

int	handle_hex(t_element *element)
{
	unsigned int		value;
	char				*hex_str;
	char				*upper_hex_str;
	int					printed;

	value = (unsigned int)(unsigned long long)element->content;
	hex_str = ft_utohex(value);
	if (!hex_str)
		return (-1);
	if (element->spec == 'X')
	{
		upper_hex_str = ft_toupper_string(hex_str);
		free(hex_str);
		if (!upper_hex_str)
			return (-1);
		element->content = (void *)upper_hex_str;
	}
	else
		element->content = (void *)hex_str;
	printed = handle_str(element);
	return (printed);
}

int	handle_pointer(t_element *element)
{
	char				*ptr_str;
	int					printed;

	if (element->content == NULL)
		ptr_str = ft_strdup("(nil)");
	else
		ptr_str = ft_ptoa((unsigned long long)element->content);
	if (!ptr_str)
		return (-1);
	element->content = (void *)ptr_str;
	printed = handle_str(element);
	return (printed);
}

int	handle_str(t_element *element)
{
	char	*str;
	int		printed;
	char	*formatted_str;
	int		len;

	str = (char *)element->content;
	formatted_str = str;
	printed = 0;
	if (element->spec == 'c' && str[0] == '\0')
		return (handle_null_char_with_padding(element));
	if (has_option(element))
	{
		formatted_str = handle_options(element);
		if (!formatted_str)
			return (-1);
		len = ft_strlen(formatted_str);
		printed += write(1, formatted_str, len);
		if (element->spec == 'c' && formatted_str[0] == '\0')
			printed += write(1, "\0", 1);
	}
	else
		printed = write(1, str, ft_strlen(str));
	element->content = (void *)formatted_str;
	return (printed);
}
