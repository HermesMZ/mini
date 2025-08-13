/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:14:40 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/26 16:44:59 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putresult_ll(char *result, long long nb, size_t *i)
{
	if (nb >= 10)
	{
		ft_putresult_ll(result, nb / 10, i);
		ft_putresult_ll(result, nb % 10, i);
	}
	else
		result[(*i)++] = (char)nb + '0';
}

static size_t	ft_digits_count_ll(long long nb)
{
	size_t	i;

	if (nb == 0)
		return (1);
	i = 0;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_ll(long long n)
{
	char		*result;
	size_t		result_size;
	size_t		i;
	long long	nb;

	i = 0;
	nb = n;
	result_size = ft_digits_count_ll(nb);
	result = (char *)malloc(sizeof(char) * (result_size + 1));
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		result[i++] = '-';
		nb *= -1;
	}
	if (n == 0)
		result[i++] = '0';
	else
		ft_putresult_ll(result, nb, &i);
	result[result_size] = '\0';
	return (result);
}
