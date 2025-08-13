/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_nod.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:21:08 by MZimeris          #+#    #+#             */
/*   Updated: 2025/06/11 16:22:18 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_node(t_list **head, t_list *node_to_delete,
			void (*del)(void*))
{
	t_list	*current;
	t_list	*prev_node;

	if (!head || !*head || !node_to_delete)
		return ;
	if (*head == node_to_delete)
	{
		*head = node_to_delete->next;
		ft_lstdelone(node_to_delete, del);
		return ;
	}
	current = *head;
	prev_node = NULL;
	while (current && current != node_to_delete)
	{
		prev_node = current;
		current = current->next;
	}
	if (current == node_to_delete)
	{
		prev_node->next = current->next;
		ft_lstdelone(node_to_delete, del);
	}
}
