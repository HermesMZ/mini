/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:31:33 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 17:24:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_unlink(t_pipex *pipex)
{
	if (strcmp(pipex->infile, "here_doc") == 0)
	{
		if (unlink("here_doc") < 0)
			perror("Error unlinking here_doc file");
	}
}

int	check_heredoc_fd(t_pipex *pipex)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open("here_doc", O_RDONLY);
	if (infile_fd < 0)
	{
		perror("here_doc");
		return (-1);
	}
	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		perror(pipex->outfile);
		close(infile_fd);
		return (-2);
	}
	close(infile_fd);
	close(outfile_fd);
	return (0);
}

int	here_doc_parse_args(t_pipex *pipex, int argc, char *argv[])
{
	int	i;

	i = 0;
	pipex->outfile = ft_my_malloc(pipex->allocator,
			ft_strlen(argv[argc - 1]) + 1);
	if (!pipex->outfile)
		return (-1);
	ft_strlcpy(pipex->outfile, argv[argc - 1], ft_strlen(argv[argc - 1]) + 1);
	pipex->cmds = init_cmds(pipex->allocator, argc - 4);
	if (!pipex->cmds)
		return (-1);
	while (i < argc - 4)
	{
		if (parse_one_command(pipex, argv[i + 3], pipex->cmds, i) < 0)
			return (-1);
		i++;
	}
	if (check_heredoc_fd(pipex) < 0)
		return (-1);
	return (0);
}

int	here_doc(t_pipex *pipex, int argc, char *argv[])
{
	char	*line;
	int		temp_fd;

	temp_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd < 0)
		return (perror("here_doc"), -1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
			&& line[ft_strlen(argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	get_next_line(-1);
	if (here_doc_parse_args(pipex, argc, argv) < 0)
		return (-1);
	return (0);
}

int	pipex_heredoc(t_pipex *pipex)
{
	int	i;
	int	in_fd;
	int	last_exit_status;

	i = 0;
	in_fd = open(pipex->infile, O_RDONLY);
	if (in_fd < 0)
	{
		perror(pipex->infile);
		in_fd = -1;
	}
	while (pipex->cmds[i])
	{
		in_fd = exec_bonus(pipex, i, in_fd);
		if (in_fd < 0)
			return (-1);
		i++;
	}
	last_exit_status = wait_for_children(pipex->last_pid);
	return (last_exit_status);
}
