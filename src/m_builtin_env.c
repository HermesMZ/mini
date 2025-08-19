/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 13:00:00 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

int	print_export(t_env **env)
{
	t_env_node	*current;

	if (!env || !*env)
		return (0);
	current = (*env)->env_list;
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

int	handle_env(t_env *env)
{
	t_env_node	*current;

	if (!env)
		return (1);

	current = env->env_list;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	handle_export(t_env **env, t_command *command)
{
	char		**kval;
	int			i;
	t_env_node	*node;

	if (!command->args || !command->args[0])
		return (print_export(env));
	i = 0;
	while (command->args[i])
	{
		kval = ft_split(command->args[i]->string, '=');
		if (kval && kval[0])
		{
			node = get_env(*env, kval[0]);
			if (node)
			{
				free(node->value);
				if (kval[1])
					node->value = ft_strdup(kval[1], ft_strlen(kval[1]), 0);
				else
					node->value = ft_strdup("", 0, 0);
			}
			else if (kval[1])
				create_env_node(env, kval[0], kval[1]);
			else
				create_env_node(env, kval[0], "");
			if (ft_strcmp(kval[0], "PATH") == 0 && kval[1])
			{
				if ((*env)->path)
					free_splitted((*env)->path);
				(*env)->path = ft_split(kval[1], ':');
			}
		}
		if (kval)
			free_splitted(kval);
		i++;
	}
	return (0);
}

int	handle_unset(t_env **env, t_command *command)
{
	t_env_node	*current;
	t_env_node	*prev;
	int			i;

	if (!command->args[0])
		return (0);
	i = 0;
	while (command->args[i])
	{
		current = (*env)->env_list;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->key, command->args[i]->string) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					(*env)->env_list = current->next;
				if (ft_strcmp(current->key, "PATH") == 0 && (*env)->path)
				{
					free_splitted((*env)->path);
					(*env)->path = NULL;
				}
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
