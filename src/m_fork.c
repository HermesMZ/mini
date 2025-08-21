/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:12:16 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/21 13:20:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_clean_parent(t_env *env, t_pipe_data *pipe_data, int pid)
{
	env->last_pid = pid;
	if (pipe_data->in_fd > 0)
		close(pipe_data->in_fd);
	if (pipe_data->out_fd > 1)
		close(pipe_data->out_fd);
	if (pipe_data->is_piped)
		close(pipe_data->pipe_fd[1]);
}

int	fork_and_exec(t_env *env, t_command *command, t_pipe_data *pipe_data)
{
	int	pid;

	pipe_data->is_piped = (command->next != NULL);
	if (ft_strcmp(command->cmd->string, "exit") == 0 && !pipe_data->is_piped)
		return (exec_builtins(command, env));
	if (pipe_data->is_piped && pipe(pipe_data->pipe_fd) < 0)
		return (handle_system_error("Pipe creation failed"), -1);
	pid = fork();
	if (pid < 0)
		return (handle_system_error("Fork failed"), -1);
	if (pid == 0)
		exec_child(env, command, pipe_data);
	else
	{
		_clean_parent(env, pipe_data, pid);
		return (pipe_data->pipe_fd[0]);
	}
	return (-1);
}

int	wait_for_children(void)
{
	int		status;
	int		last_exit_status;
	int		sig;
	pid_t	waited_pid;

	last_exit_status = 0;
	waited_pid = 1;
	while (waited_pid > 0)
	{
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig != SIGPIPE)
				last_exit_status = 128 + sig;
		}
		waited_pid = wait(&status);
	}
	return (last_exit_status);
}
