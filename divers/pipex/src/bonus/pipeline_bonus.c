/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:48:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 17:24:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	setup_bonus_input_output(t_pipex *pipex, int *in_fd,
		int *outfile_error)
{
	int	outfile_test;

	*outfile_error = 0;
	outfile_test = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_test < 0)
	{
		perror(pipex->outfile);
		*outfile_error = 1;
	}
	else
		close(outfile_test);
	*in_fd = open(pipex->infile, O_RDONLY);
	if (*in_fd < 0)
	{
		perror(pipex->infile);
		*in_fd = -1;
	}
	return (0);
}

static int	execute_bonus_pipeline(t_pipex *pipex, int in_fd)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		in_fd = exec_bonus(pipex, i, in_fd);
		if (in_fd < 0)
			return (-1);
		i++;
	}
	return (wait_for_children(pipex->last_pid));
}

int	pipex_bonus(t_pipex *pipex)
{
	int	in_fd;
	int	last_exit_status;
	int	outfile_error;

	setup_bonus_input_output(pipex, &in_fd, &outfile_error);
	last_exit_status = execute_bonus_pipeline(pipex, in_fd);
	if (last_exit_status < 0)
		return (-1);
	if (outfile_error)
		return (1);
	return (last_exit_status);
}
