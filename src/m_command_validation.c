/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_command_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 18:52:44 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

static char	*build_command_path(char *dir, char *command)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, command);
	free(temp);
	return (path);
}

int	check_system_command(t_env *env, t_command *command)
{
	char	*full_path;
	int		i;

	if (!env || !command || !command->cmd)
		return (-1);
	if (ft_strchr(command->cmd->string, '/'))
	{
		if (access(command->cmd->string, F_OK | X_OK) == 0)
			return (0);
		return (-1);
	}
	if (!env->path)
		return (-1);
	i = 0;
	while (env->path[i])
	{
		full_path = build_command_path(env->path[i], command->cmd->string);
		if (full_path)
		{
			if (access(full_path, F_OK | X_OK) == 0)
			{
				free(command->cmd->string);
				command->cmd->string = full_path;
				return (0);
			}
			free(full_path);
		}
		i++;
	}
	return (-1);
}

int	check_command(t_env *env, t_command *command)
{
	if (!command || !command->cmd)
		return (0);
	if (ft_strcmp(command->cmd->string, "cd") == 0
		|| ft_strcmp(command->cmd->string, "pwd") == 0
		|| (ft_strcmp(command->cmd->string, "echo") == 0
			&& command->args && command->args[0]
			&& ft_strcmp(command->args[0]->string, "-n") == 0)
		|| ft_strcmp(command->cmd->string, "export") == 0
		|| ft_strcmp(command->cmd->string, "unset") == 0
		|| ft_strcmp(command->cmd->string, "env") == 0
		|| ft_strcmp(command->cmd->string, "exit") == 0)
		return (0);
	return (check_system_command(env, command));
}
