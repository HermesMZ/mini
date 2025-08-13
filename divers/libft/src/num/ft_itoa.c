/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MZimeris <MZimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:16:45 by MZimeris          #+#    #+#             */
/*   Updated: 2025/04/30 23:16:46 by MZimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putresult(char *result, long nb, size_t *i)
{
	if (nb >= 10)
	{
		ft_putresult(result, nb / 10, i);
		ft_putresult(result, nb % 10, i);
	}
	else
		result[(*i)++] = nb + '0';
}

static size_t	ft_digits_count(long nb)
{
	size_t		i;

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

char	*ft_itoa(int n)
{
	char	*result;
	size_t	result_size;
	size_t	i;
	long	nb;

	i = 0;
	nb = n;
	result_size = ft_digits_count(nb);
	result = (char *)malloc(sizeof(char) * result_size + 1);
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
		ft_putresult(result, nb, &i);
	result[result_size] = '\0';
	return (result);
}
