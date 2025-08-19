/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:46:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 19:02:17 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "m_minishell.h"

static int	setup_input_output(char *outfile, char *infile, int *in_fd,
			int *outfile_error)
{
	int	outfile_test;

	*outfile_error = 0;
	if (outfile && outfile[0] != '\0')
		outfile_test = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_test < 0)
	{
		perror(outfile);
		*outfile_error = 1;
	}
	else
		close(outfile_test);
	*in_fd = open(infile, O_RDONLY);
	if (*in_fd < 0)
	{
		perror(infile);
		*in_fd = -1;
	}
	return (0);
}

static int	execute_pipeline(t_env **env, t_command *cmd, int in_fd, char *outfile)
{
	while (cmd)
	{
		in_fd = fork_and_exec(env, cmd, in_fd, outfile);
		if (in_fd < 0)
			return (-1);
		cmd = cmd->next;
	}
	return (wait_for_children((*env)->last_pid));
}

int	pipexecution(t_env **env, t_command **cmd, char *infile, char *outfile)
{
	int	in_fd;
	int	outfile_error;

	setup_input_output(outfile, infile, &in_fd, &outfile_error);
	(*env)->last_exit_status = execute_pipeline(env, *cmd, in_fd, outfile);
	if ((*env)->last_exit_status < 0)
		return (-1);
	if (outfile_error)
		return (1);
	return ((*env)->last_exit_status);
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
