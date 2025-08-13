/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:11:57 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	hard_text(const char *format, t_element **elements, size_t *j)
{
	size_t		size;
	t_element	*element;

	size = 0;
	element = new_empty_element();
	if (!element)
		return (0);
	element->spec = 's';
	element->handler = NULL;
	while (format[size] != '\0' && format[size] != '%')
		size++;
	element->content = malloc(sizeof(char) * (size + 1));
	if (!element->content)
	{
		free(element);
		return (0);
	}
	else
	{
		ft_strlcpy(element->content, format, size + 1);
		elements[*j] = element;
		(*j)++;
		return (size);
	}
}

static t_element	**check_parsing(const char *format, t_element **elements,
	int parsed_len)
{
	if (parsed_len == 0 && *format != '\0')
		return (NULL);
	return (elements);
}

t_element	**parse_format_string(const char *format, va_list al)
{
	size_t		i;
	size_t		j;
	t_element	**elements;
	size_t		parsed_len;

	i = 0;
	j = 0;
	parsed_len = 0;
	elements = create_tab(format);
	if (!elements)
		return (NULL);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			parsed_len = arg_parsing(&format[i], elements, al, &j);
		}
		else
			parsed_len = hard_text(&format[i], elements, &j);
		if (parsed_len == 0)
			break ;
		i += parsed_len;
	}
	return (check_parsing(&format[i], elements, parsed_len));
}
