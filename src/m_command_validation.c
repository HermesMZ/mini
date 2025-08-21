/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_command_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/20 18:36:13 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_check_in_path(char *path, t_command *command)
{
	char	*full_path;
	int		result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, command->cmd->string);
	free(temp);
	if (!full_path)
		return (-1);
	result = access(full_path, F_OK | X_OK);
	if (result == 0)
	{
		free(command->cmd->string);
		command->cmd->string = full_path;
		return (0);
	}
	return (result);
}

static int	_check_system_command(t_env *env, t_command *command)
{
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
		if (_check_in_path(env->path[i], command) == 0)
			return (0);
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
	return (_check_system_command(env, command));
}
