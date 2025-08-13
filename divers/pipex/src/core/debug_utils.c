/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:00:06 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/11 18:46:07 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	debug_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argv)
	{
		ft_printf("Debug Argv:\n");
		while (i < argc)
		{
			if (argv[i] == NULL)
				ft_putstr_fd("  Arg NULL\n", 2);
			else if (argv[i][0] == '\0')
				ft_putstr_fd("  Arg Empty\n", 2);
			else
				ft_printf("  Arg %d: %s\n", i, argv[i]);
			i++;
		}
	}
	else
		ft_putstr_fd("Debug Argv: NULL\n", 2);
	ft_printf("End of Debug Argv\n\n");
}

void	debug_print_pipex_info(t_pipex *pipex)
{
	int	i;

	if (!pipex)
	{
		ft_putstr_fd("Pipex structure is NULL\n", 2);
		return ;
	}
	ft_printf("Pipex Info:\n");
	ft_printf("Infile: %s\n", pipex->infile);
	ft_printf("Outfile: %s\n", pipex->outfile);
	if (pipex->cmds)
	{
		i = 0;
		while (pipex->cmds[i])
		{
			ft_printf("Command %d: |%s|\n", i + 1, pipex->cmds[i][0]);
			if (pipex->cmds[i][1])
				ft_printf("Argument 1: |%s|\n", pipex->cmds[i][1]);
			i++;
		}
	}
	ft_printf("End of Pipex Info\n\n");
}
