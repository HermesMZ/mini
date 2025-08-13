/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:15:35 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/17 20:15:37 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	parse_precision(const char *format, t_element *element)
{
	size_t	i;

	i = 0;
	if (format[i] == '.')
	{
		i++;
		if (ft_isdigit(format[i]))
		{
			element->precision = ft_atoi(&format[i]);
			while (ft_isdigit(format[i]))
				i++;
			return (i);
		}
		else
		{
			element->precision = 0;
			return (1);
		}
	}
	return (0);
}

static size_t	parse_width(const char *format, t_element *element)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(format[i]))
	{
		element->width = ft_atoi(&format[i]);
		while (ft_isdigit(format[i]))
			i++;
	}
	return (i);
}

size_t	flag_parsing(const char *format, t_element *element)
{
	size_t	i;

	i = 0;
	while (is_flag(format[i]))
	{
		if (format[i] == '-')
			element->has_minus = 1;
		else if (format[i] == '0')
			element->has_zero = 1;
		else if (format[i] == '#')
			element->has_hash = 1;
		else if (format[i] == '+')
			element->has_plus = 1;
		else if (format[i] == ' ')
			element->has_space = 1;
		i++;
	}
	i += parse_width(&format[i], element);
	i += parse_precision(&format[i], element);
	return (i);
}
