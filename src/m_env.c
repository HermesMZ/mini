/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:30:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 17:34:07 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

t_env	*create_env_node_only(char *key, char *value)
{
	t_env	*new_node;

	if (!key)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key, ft_strlen(key), 0);
	if (value)
		new_node->value = ft_strdup(value, ft_strlen(value), 0);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	create_env_node(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node_only(key, value);
	if (new_node)
		add_env_node(env, new_node);
}

void	add_env_node(t_env **env, t_env *new)
{
	t_env	*last;

	if (!env || !new)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

static t_env	*extract_env_node(char *line)
{
	char	**kval;
	t_env	*node;

	kval = ft_split(line, '=');
	if (!kval || !kval[0])
	{
		if (kval)
			free_splitted(kval);
		return (NULL);
	}
	node = create_env_node_only(kval[0], kval[1]);
	free_splitted(kval);
	return (node);
}

t_env	*extract_env(char **envp, t_env **env)
{
	char	*line;

	line = NULL;
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		line = ft_strdup(*envp, ft_strlen(*envp), 0);
		add_env_node(env, extract_env_node(line));
		free(line);
		line = NULL;
		envp++;
	}
	return (*env);
}
