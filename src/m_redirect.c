/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:17:55 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/20 22:04:01 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input_redirect(int in_fd)
{
	if (in_fd > 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

static void	setup_pipe_output(int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	setup_file_output(char *outfile)
{
	int	outfile_fd;

	if (!outfile)
		return ;
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd >= 0)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
}

int	setup_output_redirect(t_command *command, int pipe_fd[2], char *outfile)
{
	if (command->next != NULL)
		setup_pipe_output(pipe_fd);
	else if (outfile)
		setup_file_output(outfile);
	return (0);
}
