/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:36:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 17:47:02 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

int	handle_echo_n(t_command *command)
{
	int	i;

	i = 0;
	while (command->args[1]->string
		&& command->args[1]->string[i] != '\n'
		&& command->args[1]->string[i] != '\0')
	{
		write(1, &command->args[1]->string[i], 1);
		i++;
	}
	return (0);
}

int	handle_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd));
	return (-1);
}

int	handle_exit(t_command *command, t_env **env, t_token **token)
{
	clear_env(env);
	free_command_chain(&command);
	ft_tokenlstclear(token);
	exit(0);
}

int	exec_builtins(t_command *command, t_env **env, t_token **token)
{
	if (!command || !command->cmd)
		return (0);
	if (ft_strcmp(command->cmd->string, "cd") == 0)
		return (handle_cd(command));
	if (ft_strcmp(command->cmd->string, "pwd") == 0)
		return (handle_pwd());
	if (ft_strcmp(command->cmd->string, "echo") == 0
		&& command->args && command->args[0]
		&& ft_strcmp(command->args[0]->string, "-n") == 0)
		return (handle_echo_n(command));
	if (ft_strcmp(command->cmd->string, "export") == 0)
		return (handle_export(env, command));
	if (ft_strcmp(command->cmd->string, "unset") == 0)
		return (handle_unset(env, command));
	if (ft_strcmp(command->cmd->string, "env") == 0)
		return (handle_env(*env));
	if (ft_strcmp(command->cmd->string, "exit") == 0)
		return (handle_exit(command, env, token));
	printf("Commande '%s' non reconnue comme builtin\n", command->cmd->string);
	return (36);
}
