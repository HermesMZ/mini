/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:12:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 16:29:26 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex_data;
	int		exit_status;

	if (argc != 5)
		return (ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n",
				2), 1);
	pipex_data = init_pipex(NULL, envp);
	if (!pipex_data)
		return (1);
	if (parse_args(pipex_data, argc, argv) < 0)
	{
		return (free_pipex(pipex_data), 1);
	}
	exit_status = pipex(pipex_data);
	free_pipex(pipex_data);
	if (exit_status == -1)
		return (1);
	return (exit_status);
}
