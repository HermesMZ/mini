/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:32:18 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 17:34:32 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

int	print_export(t_env **env)
{
	t_env	*current;

	if (!env || !*env)
		return (0);
	current = *env;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
	return (0);
}

static void	del_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	remove_env_node(t_env **env, t_env *node)
{
	t_env	*current;
	t_env	*prev_node;

	if (!env || !node)
		return ;
	if (ft_strcmp((*env)->key, node->key) == 0)
	{
		*env = node->next;
		del_env_node(node);
		return ;
	}
	current = *env;
	prev_node = NULL;
	while (current && ft_strcmp(current->key, node->key) != 0)
	{
		prev_node = current;
		current = current->next;
	}
	if (current && ft_strcmp(current->key, node->key) == 0)
	{
		prev_node->next = current->next;
		del_env_node(node);
	}
}

void	clear_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		del_env_node(tmp);
	}
}
