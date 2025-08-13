/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:48:41 by zoum              #+#    #+#             */
/*   Updated: 2025/08/13 14:05:19 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

// liste chainee pour les variables d'environnement
int	handle_export(t_env *env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*current;

	if (!key || !value || !env)
		return (0);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (-1);
	new_env->key = ft_strdup(key, ft_strlen(key), 0);
	new_env->value = ft_strdup(value, ft_strlen(value), 0);
	new_env->next = NULL;

	current = env;
	while (current->next && ft_strcmp(current->next->key, key) != 0)
		current = current->next;
		current->next = new_env;
	return (0);
}
	// free current->next if it exists

int	handle_unset(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!key || !env)
		return (0);
	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	handle_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
