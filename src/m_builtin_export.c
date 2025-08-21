/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:54:38 by zoum              #+#    #+#             */
/*   Updated: 2025/08/20 18:01:07 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_print_export(t_env *env)
{
	t_env_node	*current;

	if (!env)
		return (0);
	current = env->env_list;
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

static void	_update_env_node(t_env_node *node, char *value)
{
	if (node->value)
		free(node->value);
	if (value)
		node->value = ft_strdup(value, ft_strlen(value), 0);
	else
		node->value = ft_strdup("", 0, 0);
}

static void	_create_env_node(t_env *env, char **kval)
{
	if (kval[1])
		create_env_node(env, kval[0], kval[1]);
	else
		create_env_node(env, kval[0], "");
	if (ft_strcmp(kval[0], "PATH") == 0 && kval[1])
	{
		if (env->path)
			free_splitted(env->path);
		env->path = ft_split(kval[1], ':');
	}
}

int	handle_export(t_env *env, t_command *command)
{
	char		**kval;
	int			i;
	t_env_node	*node;

	if (!command->args || !command->args[0])
		return (_print_export(env));
	i = 0;
	while (command->args[i])
	{
		kval = ft_split(command->args[i]->string, '=');
		if (kval && kval[0])
		{
			node = get_env(env, kval[0]);
			if (node)
				_update_env_node(node, kval[1]);
			else
				_create_env_node(env, kval);
		}
		if (kval)
			free_splitted(kval);
		i++;
	}
	return (0);
}
