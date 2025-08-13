/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:00:11 by mzimeris          #+#    #+#             */
/*   Updated: 2025/06/14 16:27:28 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_elem	*ft_dlstnew_elem(void *content)
{
	t_elem	*new;

	new = (malloc(sizeof(t_elem)));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->content = content;
	return (new);
}
