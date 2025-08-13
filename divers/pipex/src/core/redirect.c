/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:17:55 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 15:14:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_input_redirect(int in_fd)
{
	int	null_fd;

	if (in_fd > 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (in_fd == -1)
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
		}
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
	int	null_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror(outfile);
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDOUT_FILENO);
			close(null_fd);
		}
	}
	else
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
}

int	setup_output_redirect(t_pipex *pipex, int i, int pipe_fd[2], char *outfile)
{
	if (pipex->cmds[i + 1] != NULL)
		setup_pipe_output(pipe_fd);
	else
		setup_file_output(outfile);
	return (0);
}
