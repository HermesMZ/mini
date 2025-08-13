/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pad_pre_num.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:00:19 by MZimeris          #+#    #+#             */
/*   Updated: 2025/05/22 14:00:22 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*build_padded_str(char *prefix, char *num_str, int zeros)
{
	int		prefix_len;
	int		num_len;
	char	*res;
	int		i;

	prefix_len = 0;
	num_len = ft_strlen(num_str);
	i = 0;
	if (prefix)
		prefix_len = ft_strlen(prefix);
	res = malloc(prefix_len + zeros + num_len + 1);
	if (!res)
		return (NULL);
	if (prefix)
	{
		ft_memcpy(res + i, prefix, prefix_len);
		i += prefix_len;
	}
	while (zeros-- > 0)
		res[i++] = '0';
	ft_memcpy(res + i, num_str, num_len);
	i += num_len;
	res[i] = '\0';
	return (res);
}

static void	prepare_num_str(char **num_str, char *str, char **prefix, int *len)
{
	*prefix = NULL;
	*len = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
	{
		*prefix = ft_strndup(str, 1);
		*num_str = str + 1;
		(*len)--;
	}
	else if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		*prefix = ft_strndup(str, 2);
		*num_str = str + 2;
		(*len) -= 2;
	}
	else
	{
		*prefix = NULL;
		*num_str = str;
	}
}

static int	get_target_len(t_element *element, int len, char *prefix)
{
	int	target_len;

	if (element->precision > -1)
		target_len = element->precision;
	else if (element->has_zero && element->width && !element->has_minus)
	{
		if (prefix)
			target_len = element->width - (int)ft_strlen(prefix);
		else
			target_len = element->width;
	}
	else
		target_len = len;
	return (target_len);
}

char	*apply_precision_nbr(t_element *element, char *str)
{
	int		len;
	int		zeros;
	char	*prefix;
	char	*num_str;
	char	*ret;

	if (element->precision == 0 && ft_strlen(str) == 1 && str[0] == '0')
	{
		free(str);
		return (ft_strdup(""));
	}
	prepare_num_str(&num_str, str, &prefix, &len);
	if (len >= get_target_len(element, len, prefix))
	{
		if (prefix)
			free(prefix);
		return (str);
	}
	zeros = get_target_len(element, len, prefix) - len;
	ret = build_padded_str(prefix, num_str, zeros);
	if (prefix)
		free(prefix);
	free(str);
	return (ret);
}
