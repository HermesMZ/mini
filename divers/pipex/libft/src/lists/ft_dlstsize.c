/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:14:18 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/11 18:52:18 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_dblist **lst)
{
	t_elem	*elem;
	int		i;

	elem = (*lst)->first;
	i = 0;
	while (elem)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}
