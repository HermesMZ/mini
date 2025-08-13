/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:53:06 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/16 21:16:31 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dlstinit(void)
{
	t_dblist	*new_list;

	new_list = malloc(sizeof(t_dblist));
	if (!new_list)
		return (NULL);
	new_list->first = NULL;
	new_list->last = NULL;
	new_list->length = 0;
	return (new_list);
}
