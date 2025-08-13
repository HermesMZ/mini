/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:41:30 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_precision_zero(char *str)
{
	char	*empty_str;

	empty_str = malloc(1);
	if (!empty_str)
		return (NULL);
	empty_str[0] = '\0';
	free(str);
	return (empty_str);
}

static char	*apply_precision_str(t_element *element, char *str)
{
	char	*result;
	int		len;

	if (element->precision >= 0)
	{
		if (element->precision == 0)
		{
			free(str);
			return (ft_strdup(""));
		}
		len = ft_strlen(str);
		if (element->precision < len)
			len = element->precision;
		result = ft_substr(str, 0, len);
		free(str);
		return (result);
	}
	return (str);
}

char	*apply_precision(t_element *element, char *str)
{
	char	*result;

	if (element->spec == 's' || element->spec == 'c')
	{
		if (element->spec == 'c' && element->precision == 0)
			element->precision = -1;
		if (element->spec == 's' && element->precision == 0)
		{
			free(str);
			return (ft_strdup(""));
		}
		else
			result = apply_precision_str(element, str);
	}
	else if (element->spec == 'd' || element->spec == 'i'
		|| element->spec == 'u' || element->spec == 'x'
		|| element->spec == 'X' || element->spec == 'p')
		result = apply_precision_nbr(element, str);
	else
		result = ft_strdup(str);
	return (result);
}
