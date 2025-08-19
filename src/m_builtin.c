/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 18:33:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

int	handle_echo_n(t_command *command)
{
	int	i;

	i = 2;
	while (command->args[i])
	{
		write(1, command->args[i], ft_strlen(command->args[i]->string));
		if (command->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (0);
}

int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	handle_exit(t_command *command, t_env **env)
{
	clear_env(env);
	free_command_chain(&command);
	exit(0);
}


