/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:10:28 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_handler	find_format_handler(char spec)
{
	const t_format	g_format_handlers[] = {
	{'c', handle_char},
	{'s', handle_str},
	{'d', handle_number},
	{'i', handle_number},
	{'u', handle_number},
	{'x', handle_hex},
	{'X', handle_hex},
	{'p', handle_pointer},
	{'%', handle_char},
	{'\0', NULL}
	};
	const t_format	*current = g_format_handlers;

	while (current->spec != '\0')
	{
		if (current->spec == spec)
		{
			return (current->handler);
		}
		current++;
	}
	return (NULL);
}

void	format_finder(t_element **elements)
{
	size_t	i;

	i = 0;
	while (elements[i])
	{
		if (elements[i]->handler == NULL)
			elements[i]->handler = find_format_handler(elements[i]->spec);
		i++;
	}
}

int	has_option(t_element *element)
{
	return (element->has_minus || element->has_zero || element->precision > -1
		|| element-> width || element->has_hash || element->has_plus
		|| element->has_space);
}

char	get_padding_char(t_element *element)
{
	char	padding_char;

	padding_char = ' ';
	if (element->has_zero && !element->has_minus)
	{
		if (element->spec == 'd' || element->spec == 'i'
			|| element->spec == 'u' || element->spec == 'x'
			|| element->spec == 'X' || element->spec == 'p')
		{
			if (element->precision == -1)
				padding_char = '0';
		}
	}
	return (padding_char);
}
