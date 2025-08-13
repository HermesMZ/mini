/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:47:32 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/23 15:47:34 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_element	*spec_parsing_simple(const char format_char,
	va_list al, t_element *element)
{
	element->spec = format_char;
	if (format_char == 'c')
		element->content = (void *)(long)(unsigned char)va_arg(al, int);
	else if (format_char == 'd' || format_char == 'i')
		element->content = (void *)(long long)va_arg(al, int);
	else if (format_char == 'u')
		element->content = (void *)(unsigned long long)va_arg(al, unsigned int);
	else if (format_char == 'x' || format_char == 'X')
		element->content
			= (void *)(unsigned long long)va_arg(al, unsigned int);
	else if (format_char == 'p')
		element->content = va_arg(al, void *);
	else if (format_char == '%')
		element->content = (void *) '%';
	return (element);
}

static t_element	*spec_parsing_string(va_list al, t_element *element)
{
	char	*tmp;

	element->spec = 's';
	tmp = va_arg(al, char *);
	if (!tmp)
		element->content = ft_strdup("(null)");
	else
		element->content = ft_strdup(tmp);
	if (!element->content)
		return (NULL);
	return (element);
}

static t_element	*spec_parsing(const char *format, va_list al,
	t_element *element)
{
	if (*format == 's')
		return (spec_parsing_string(al, element));
	else
		return (spec_parsing_simple(*format, al, element));
}

size_t	arg_parsing(const char *format, t_element **elements,
	va_list al, size_t *j)
{
	size_t		i;
	t_element	*element;

	i = 0;
	element = new_empty_element();
	if (!element)
		return (0);
	i += flag_parsing(&format[i], element);
	if (is_spec(format[i]))
	{
		element = spec_parsing(&format[i], al, element);
		i++;
	}
	elements[*j] = element;
	(*j)++;
	return (i);
}
