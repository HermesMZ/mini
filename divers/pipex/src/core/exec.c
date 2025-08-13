/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:45:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:05:56 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

int	exec_child(t_pipex *pipex, int i, int in_fd, int pipe_fd[2])
{
	int	check_result;

	setup_input_redirect(in_fd);
	if (setup_output_redirect(pipex, i, pipe_fd, pipex->outfile) < 0)
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

int	exec(t_pipex *pipex, int i, int in_fd)
{
	int	pid;
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (pipex->cmds[i + 1] != NULL && pipe(pipe_fd) < 0)
		return (handle_system_error("Pipe creation failed", pipex), -1);
	pid = fork();
	if (pid < 0)
		return (handle_system_error("Fork failed", pipex), -1);
	if (pid == 0)
		return (exec_child(pipex, i, in_fd, pipe_fd));
	pipex->last_pid = pid;
	if (in_fd > 0)
		close(in_fd);
	if (pipex->cmds[i + 1] != NULL)
		return (close(pipe_fd[1]), pipe_fd[0]);
	return (0);
}

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		last_exit_status;
	int		sig;
	pid_t	waited_pid;

	last_exit_status = 0;
	waited_pid = wait(&status);
	while (waited_pid > 0)
	{
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig != SIGPIPE)
					last_exit_status = 128 + sig;
			}
		}
		waited_pid = wait(&status);
	}
	return (last_exit_status);
}
