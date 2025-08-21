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

#include "minishell.h"

static void	del_env_node(t_env_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	remove_env_node(t_env *env, t_env_node *node)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!env || !node)
		return ;
	current = env->env_list;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (prev)
				prev->next = current->next;
			else
				env->env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	clear_env(t_env **env)
{
	t_env_node	*current;
	t_env_node	*tmp;

	if (!env || !*env)
		return ;
	current = (*env)->env_list;
	while (current)
	{
		tmp = current;
		current = current->next;
		del_env_node(tmp);
	}
	if ((*env)->path)
		free_splitted((*env)->path);
	free(*env);
	*env = NULL;
}

t_env_node	*get_env(t_env *env, const char *key)
{
	t_env_node	*current;

	if (!env || !key)
		return (NULL);
	current = env->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
