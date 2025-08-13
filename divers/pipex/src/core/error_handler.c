/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:15:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 17:03:54 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_command_not_found_error(const char *command)
{
	ft_putstr_fd((char *)command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_no_such_file_error(const char *command)
{
	ft_putstr_fd((char *)command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_permission_denied_error(const char *command)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd((char *)command, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	handle_command_error(t_pipex *pipex, int check_result, int cmd_index)
{
	const char	*command;

	command = pipex->cmds[cmd_index][0];
	if (check_result == -2)
	{
		print_permission_denied_error(command);
		free_pipex(pipex);
		exit(126);
	}
	if (check_result < 0)
	{
		if (ft_strchr(command, '/') != NULL)
			print_no_such_file_error(command);
		else
			print_command_not_found_error(command);
		free_pipex(pipex);
		exit(127);
	}
}

void	handle_system_error(const char *error_msg, t_pipex *pipex)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)error_msg, 2);
	ft_putstr_fd("\n", 2);
	if (pipex)
		free_pipex(pipex);
	exit(1);
}
