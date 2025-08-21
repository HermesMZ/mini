/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/21 23:15:01 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// <test_norights<run_valgrind.sh <Makefile cat | wc -l

static int	_handle_out_redir(t_redirect *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static int	_get_last_output_fd(t_command *cmd, t_pipe_data *pipe_data)
{
	t_redirect	*redir;
	int			fd;
	int			prev_fd;
	printf("entering get last output fd\n");
	fd = -1;
	prev_fd = -1;
	pipe_data->outfile_error = 0;
	redir = cmd->redirects;
	while (redir)
	{
	printf("entering get last output fd loop\n");
		
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
	printf("entering get last output fd condition\n");

			if (prev_fd != -1)
				close(prev_fd);
			fd = _handle_out_redir(redir);
			if (fd < 0)
			{
				perror(redir->filename);
				pipe_data->outfile_error = 1;
				return (fd);
			}
			prev_fd = fd;
		}
		redir = redir->next;
	}
	if (prev_fd != -1)
		return (prev_fd);
	return (-1);
}

static int	_get_last_input_fd(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	fd = -1;
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (fd > 0)
				close(fd);
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->filename);
				return (-1);
			}
		}
		redir = redir->next;
	}
	return (fd);
}

static void	_pipexecution_clean_fds(t_pipe_data *pipe_data)
{
	if (pipe_data->outfile_error)
	{
		if (pipe_data->redir_in_fd > 0)
			close(pipe_data->redir_in_fd);
		if (pipe_data->in_fd > 0)
			close(pipe_data->in_fd);
		pipe_data->in_fd = -1;
		return ;
	}
	if (pipe_data->redir_in_fd > 0)
	{
		if (pipe_data->in_fd > 0)
			close(pipe_data->in_fd);
		pipe_data->in_fd = pipe_data->redir_in_fd;
	}
	else
		pipe_data->in_fd = STDIN_FILENO;
}

int	pipexecution(t_env *env, t_command *cmd)
{
	t_pipe_data	*pipe_data;

	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		return (-1);
	*pipe_data = (t_pipe_data){0};
	while (cmd)
	{
		if (cmd->redirects)
		{
			pipe_data->redir_in_fd = _get_last_input_fd(cmd);
			if (pipe_data->redir_in_fd < 0)
				return (free(pipe_data), -1);
			pipe_data->out_fd = _get_last_output_fd(cmd, pipe_data);
			if (pipe_data->out_fd < 0)
				return (free(pipe_data), -1);
		}
		_pipexecution_clean_fds(pipe_data);
		pipe_data->in_fd = fork_and_exec(env, cmd, pipe_data);
		if (pipe_data->in_fd < 0 || pipe_data->outfile_error)
		{
			free(pipe_data);
			return (wait_for_children(), -1);
		}
		cmd = cmd->next;
	}
	free(pipe_data);
	return (wait_for_children());
}

// int	pipexecution(t_env *env, t_command *cmd)
// {
// 	t_pipe_data	*pipe_data;

// 	pipe_data = malloc(sizeof(t_pipe_data));
// 	if (!pipe_data)
// 		return (-1);
// 	*pipe_data = (t_pipe_data){0};

// }

// printf("pipe data in_fd=%d, out_fd=%d, pipe_fd[0]=%d, pipe_fd[1]=%d,
// 	error=%d\n", pipe_data->in_fd, pipe_data->out_fd,
// 	pipe_data->pipe_fd[0], pipe_data->pipe_fd[1], pipe_data->outfile_error);