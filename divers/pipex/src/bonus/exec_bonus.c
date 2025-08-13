/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:20:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:02:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	setup_heredoc_output(char *outfile)
{
	int	outfile_fd;
	int	null_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	setup_heredoc_redirect(t_pipex *pipex, int i, int pipe_fd[2], char *outfile)
{
	if (pipex->cmds[i + 1] != NULL)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	else
		setup_heredoc_output(outfile);
	return (0);
}

int	exec_child_bonus(t_pipex *pipex, int i, int in_fd, int pipe_fd[2])
{
	int	check_result;

	setup_input_redirect(in_fd);
	if (setup_heredoc_redirect(pipex, i, pipe_fd, pipex->outfile) < 0)
	{
		free_pipex(pipex);
		exit(1);
	}
	check_result = check_command(pipex, pipex->cmds[i][0], i);
	handle_command_error(pipex, check_result, i);
	execve(pipex->cmds[i][0], pipex->cmds[i], pipex->envp);
	perror("execve");
	free_pipex(pipex);
	exit(127);
}

int	exec_bonus(t_pipex *pipex, int i, int in_fd)
{
	int	pid;
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (pipex->cmds[i + 1] != NULL && pipe(pipe_fd) < 0)
	{
		handle_system_error("Pipe creation failed", pipex);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		handle_system_error("Fork failed", pipex);
		return (-1);
	}
	if (pid == 0)
		return (exec_child_bonus(pipex, i, in_fd, pipe_fd));
	pipex->last_pid = pid;
	if (in_fd > 0)
		close(in_fd);
	if (pipex->cmds[i + 1] != NULL)
		return (close(pipe_fd[1]), pipe_fd[0]);
	return (0);
}
