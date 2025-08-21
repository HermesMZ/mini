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

#include "minishell.h"

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

static void	_clean_unset(t_env_node **current, t_env_node **prev, t_env *env)
{
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		env->env_list = (*current)->next;
	if (ft_strcmp((*current)->key, "PATH") == 0 && env->path)
	{
		free_splitted(env->path);
		env->path = NULL;
	}
	free((*current)->key);
	free((*current)->value);
	free(*current);
}

int	handle_unset(t_env *env, t_command *command)
{
	t_env_node	*current;
	t_env_node	*prev;
	int			i;

	if (!command->args[0])
		return (0);
	i = 0;
	while (command->args[i])
	{
		current = env->env_list;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->key, command->args[i]->string) == 0)
			{
				_clean_unset(&current, &prev, env);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
