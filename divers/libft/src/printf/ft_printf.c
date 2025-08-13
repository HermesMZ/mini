/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:14:50 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:05:11 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	free_elements(t_element **elements)
{
	size_t	i;

	i = 0;
	if (elements)
	{
		while (elements[i] != NULL)
		{
			if (elements[i]->content && (elements[i]->spec == 's'
					|| elements[i]->spec == 'c' || elements[i]->spec == 'p'
					|| elements[i]->spec == 'd' || elements[i]->spec == 'i'
					|| elements[i]->spec == 'u' || elements[i]->spec == 'x'
					|| elements[i]->spec == 'X'))
			{
				free(elements[i]->content);
				elements[i]->content = NULL;
			}
			free(elements[i]);
			elements[i] = NULL;
			i++;
		}
		free(elements);
		elements = NULL;
	}
}

static size_t	elements_count(t_element **elements)
{
	size_t	count;

	count = 0;
	while (elements[count])
		count++;
	return (count);
}

static size_t	print_elements(t_element **elements)
{
	size_t	total_printed;
	size_t	i;
	size_t	total_elements;
	int		printed;

	printed = 0;
	i = 0;
	total_printed = 0;
	total_elements = elements_count(elements);
	while (i < total_elements)
	{
		if (elements[i]->handler)
		{
			printed = elements[i]->handler(elements[i]);
			if (printed >= 0)
				total_printed += printed;
			else
				return (-1);
		}
		i++;
	}
	return (total_printed);
}

int	ft_printf(const char *format, ...)
{
	size_t		total_printed;
	va_list		al;
	t_element	**elements;

	total_printed = 0;
	elements = NULL;
	if (!format)
		return (-1);
	if (validate_format_string(format) == 0)
	{
		va_start(al, format);
		elements = parse_format_string(format, al);
		va_end(al);
		if (!elements)
			return (-1);
		format_finder(elements);
		total_printed = print_elements(elements);
		free_elements(elements);
	}
	else
		return (-1);
	return (total_printed);
}
