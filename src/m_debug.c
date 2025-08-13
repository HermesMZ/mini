/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_debug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:24:53 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/08 13:36:49 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	debug_print_token(t_token *token)
{
	if (!token)
		return ;
	printf("string: %s\n", token->string);
	printf("type: %d\n", token->type);
	printf("quote_type: %d\n", token->quote_type);
}

void	debug_print_all_tokens(t_token *token)
{
	t_token	*tmp_token;
	int		i;

	tmp_token = token;
	i = 1;
	while (tmp_token)
	{
		printf("Token %d:\n", i++);
		debug_print_token(tmp_token);
		tmp_token = tmp_token->next;
	}
}
