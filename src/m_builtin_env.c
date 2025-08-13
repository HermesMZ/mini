/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:48:41 by zoum              #+#    #+#             */
/*   Updated: 2025/08/13 17:32:31 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"
#include <string.h>

static void	parse_export_arg(t_command *command, char **key, char **value,
		char ***kval)
{
	*key = NULL;
	*value = NULL;
	*kval = NULL;

	if (command && command->args && command->args[0]
		&& command->args[0]->string)
	{
		if (strchr(command->args[0]->string, '='))
		{
			*kval = ft_split(command->args[0]->string, '=');
			if (*kval && (*kval)[0])
			{
				*key = (*kval)[0];
				*value = (*kval)[1];
			}
		}
		else
		{
			*key = command->args[0]->string;
		}
	}
}

static int	update_existing_var(t_env **env, char *key, char *value,
		char **kval)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value, ft_strlen(value), 0);
			}
			if (kval)
				free_splitted(kval);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	handle_export(t_env **env, t_command *command)
{
	char	*key;
	char	*value;
	char	**kval;

	if (!env)
		return (0);
	parse_export_arg(command, &key, &value, &kval);
	if (!key)
	{
		if (kval)
			free_splitted(kval);
		return (print_export(env));
	}
	if (update_existing_var(env, key, value, kval))
		return (0);
	create_env_node(env, key, value);
	if (kval)
		free_splitted(kval);
	return (0);
}

int	handle_unset(t_env **env, t_command *command)
{
	t_env	*current;
	char	*key;

	if (!env || !*env)
		return (0);
	key = NULL;
	if (command && command->args && command->args[0]
		&& command->args[0]->string)
			key = command->args[0]->string;
	if (!key)
		return (0);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			remove_env_node(env, current);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

int	handle_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		else
			printf("%s=\n", current->key);
		current = current->next;
	}
	return (0);
}
