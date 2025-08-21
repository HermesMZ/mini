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

#include "minishell.h"

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

void	debug_print_env(t_env *env)
{
	t_env_node	*current;

	if (!env || !env->env_list)
	{
		printf("Environment is empty.\n");
		return ;
	}
	current = env->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		else
			printf("%s=\n", current->key);
		current = current->next;
	}
}
