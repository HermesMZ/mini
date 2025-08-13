/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:45:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:20:26 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_one_command(t_pipex *pipex, char *cmd, char ***cmds, int index)
{
	char	**args;

	if (index < 0 || !cmds || !cmd || !*cmd)
		return (-1);
	args = parse_command_with_quotes(pipex->allocator, cmd);
	if (!args)
		return (-1);
	cmds[index] = args;
	return (0);
}

static int	setup_files(t_pipex *pipex, char *infile, char *outfile)
{
	pipex->infile = ft_my_malloc(pipex->allocator, ft_strlen(infile) + 1);
	if (!pipex->infile)
		return (-1);
	ft_strlcpy(pipex->infile, infile, ft_strlen(infile) + 1);
	pipex->outfile = ft_my_malloc(pipex->allocator, ft_strlen(outfile) + 1);
	if (!pipex->outfile)
		return (-1);
	ft_strlcpy(pipex->outfile, outfile, ft_strlen(outfile) + 1);
	return (0);
}

static int	setup_commands(t_pipex *pipex, int argc, char *argv[])
{
	int	i;

	pipex->cmds = init_cmds(pipex->allocator, argc - 3);
	if (!pipex->cmds)
		return (-1);
	i = 0;
	while (i < argc - 3)
	{
		if (parse_one_command(pipex, argv[i + 2], pipex->cmds, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	parse_args(t_pipex *pipex, int argc, char *argv[])
{
	if (setup_files(pipex, argv[1], argv[argc - 1]) < 0)
		return (-1);
	if (setup_commands(pipex, argc, argv) < 0)
		return (-1);
	return (0);
}
