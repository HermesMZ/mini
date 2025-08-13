/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:45:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:22:33 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_full_path(t_lalloc *allocator, char *cmd, char *path)
{
	char	*full_path;
	char	*temp;

	temp = ft_my_malloc(allocator, ft_strlen(path) + 2);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, path, ft_strlen(path) + 1);
	ft_strlcat(temp, "/", ft_strlen(path) + 2);
	full_path = ft_strjoin_alloc(allocator, temp, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		return (full_path);
	ft_my_free(allocator, full_path);
	return (NULL);
}

static int	check_absolute_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (-1);
	if (access(cmd, X_OK) != 0)
		return (-2);
	return (0);
}

static int	search_in_path(t_pipex *pipex, char *cmd, int index)
{
	int		i;
	char	*full_path;

	i = -1;
	while (pipex->path[++i])
	{
		full_path = check_full_path(pipex->allocator, cmd, pipex->path[i]);
		if (full_path)
		{
			ft_my_free(pipex->allocator, pipex->cmds[index][0]);
			pipex->cmds[index][0] = full_path;
			return (0);
		}
	}
	return (-1);
}

int	check_command(t_pipex *pipex, char *cmd, int index)
{
	if (!cmd || !pipex)
		return (-1);
	if (!*cmd)
		return (-1);
	if (ft_strchr(cmd, '/') != NULL)
		return (check_absolute_path(cmd));
	if (!pipex->path)
		return (-1);
	return (search_in_path(pipex, cmd, index));
}
