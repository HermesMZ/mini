/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:12:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:07:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	handle_heredoc_mode(t_pipex *pipex_data, int argc, char *argv[])
{
	pipex_data->infile = "here_doc";
	if (here_doc(pipex_data, argc, argv) < 0)
		return (-1);
	return (pipex_heredoc(pipex_data));
}

static int	handle_normal_mode(t_pipex *pipex_data, int argc, char *argv[])
{
	if (parse_args(pipex_data, argc, argv) < 0)
		return (-1);
	return (pipex_bonus(pipex_data));
}

static int	cleanup_and_exit(t_pipex *pipex_data, int exit_status)
{
	here_doc_unlink(pipex_data);
	free_pipex(pipex_data);
	if (exit_status == -1)
		return (1);
	return (exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex_data;
	int		exit_status;

	if (argc < 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 ... cmd2 outfile\n",
				2), 1);
	if (strcmp(argv[1], "here_doc") == 0 && argc < 6)
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	pipex_data = init_pipex(NULL, envp);
	if (!pipex_data)
		return (1);
	if (strcmp(argv[1], "here_doc") == 0)
		exit_status = handle_heredoc_mode(pipex_data, argc, argv);
	else
		exit_status = handle_normal_mode(pipex_data, argc, argv);
	if (exit_status < 0)
		return (free_pipex(pipex_data), 1);
	return (cleanup_and_exit(pipex_data, exit_status));
}
