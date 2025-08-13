/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:28:14 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 23:04:49 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*apply_xhash(t_element *element, char *str)
{
	char	*new_str;
	int		str_len;

	str_len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (str_len + 3));
	if (!new_str)
		return (NULL);
	new_str[0] = '0';
	if (element->spec == 'x')
		new_str[1] = 'x';
	else if (element->spec == 'X')
		new_str[1] = 'X';
	ft_memcpy(&new_str[2], str, str_len);
	new_str[str_len + 2] = '\0';
	free(str);
	return (new_str);
}

static char	*apply_plus(t_element *element, char *str)
{
	char	*new_str;
	int		str_len;

	str_len = ft_strlen(str);
	if (str[0] != '-' && ft_strchr("di", element->spec))
	{
		new_str = malloc(sizeof(char) * (str_len + 2));
		if (!new_str)
			return (NULL);
		new_str[0] = '+';
		ft_memcpy(&new_str[1], str, str_len);
		new_str[str_len + 1] = '\0';
	}
	else
		new_str = ft_strdup(str);
	free(str);
	return (new_str);
}

static char	*apply_space(t_element *element, char *str)
{
	char	*new_str;
	int		str_len;

	str_len = ft_strlen(str);
	if (str[0] != '-' && str[0] != '+' && ft_strchr("di", element->spec))
	{
		new_str = malloc(sizeof(char) * (str_len + 2));
		if (!new_str)
			return (NULL);
		new_str[0] = ' ';
		ft_memcpy(&new_str[1], str, str_len);
		new_str[str_len + 1] = '\0';
	}
	else
		new_str = ft_strdup(str);
	free(str);
	return (new_str);
}

static char	*apply_flags(t_element *element, char *str)
{
	if (element->has_plus)
		str = apply_plus(element, str);
	if (element->has_space)
		str = apply_space(element, str);
	if (element->has_hash && (element->spec == 'x'
			|| element->spec == 'X') && str[0] != '0')
		str = apply_xhash(element, str);
	return (str);
}

char	*handle_options(t_element *element)
{
	char	*original_str;
	char	*formatted_str;
	char	padding_char;

	original_str = (char *)element->content;
	if (element->spec == 's' && ft_strncmp(original_str, "(null)", 6) == 0)
		formatted_str = handle_null_string(element, original_str);
	else
		formatted_str = original_str;
	formatted_str = apply_flags(element, formatted_str);
	if (element->precision > -1 || (element->has_zero
			&& element->width && !element->has_minus))
		formatted_str = apply_precision(element, formatted_str);
	padding_char = get_padding_char(element);
	if (element->width)
		formatted_str = apply_padding_width(element, formatted_str,
				padding_char);
	element->content = (void *)formatted_str;
	return (formatted_str);
}
