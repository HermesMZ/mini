/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:30:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 14:17:51 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

void	remove_env_node(t_env *env, t_env *node)
{
	t_env	*current;
	t_env	*prev_node;

	if (!env || !node)
		return ;
	if (env == node)
	{
		*env = node->next;
		del_env_node(node);
		return ;
	}
	current = *env;
	prev_node = NULL;
	while (current && current != node)
	{
		prev_node = current;
		current = current->next;
	}
	if (current == node)
	{
		prev_node->next = current->next;
		del_env_node(node);
	}
}

static void	del_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		del_env_node(tmp);
	}
}

static void	add_env_node(t_env *env, t_env *new)
{
	t_env	*last;

	if (!env || !new)
		return ;
	if (env == NULL)
	{
		env = new;
		return ;
	}
	last = env;
	while (last->next)
		last = last->next;
	last->next = new;
}


static t_env	*create_env_node(char *line)
{
	t_env	*new_node;
	char	*key;
	char	*value;
	char	*kval;

	kval = ft_split(line, '=');
	key = kval[0];
	value = kval[1];
	free(kval);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*extract_env(char **envp)
{
	t_env	*new;

	new = NULL;
	if (!envp || !*envp)
		return (new);
	while (*envp)
	{
		add_env_node(&new, create_env_node(ft_strdup(*envp,
					ft_strlen(*envp), 0)));
		envp++;
	}
	return (new);
}
