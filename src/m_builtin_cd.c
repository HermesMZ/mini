/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:24:54 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 14:16:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

static int	cd_to_home(void);
static int	cd_to_oldpwd(void);
static int	cd_expand_tilde(char *path);
static void	update_directories(char *old_cwd);

int	handle_cd(t_command *command)
{
	char	*path;
	char	cwd[PATH_MAX];
	int		result;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);
	if (!command->args[0] || command->args[0][0] == '\0')
		result = cd_to_home();
	else
	{
		path = command->string;
		if (ft_strcmp(path, "~") == 0)
			result = cd_to_home();
		else if (ft_strcmp(path, "-") == 0)
			result = cd_to_oldpwd();
		else if (path[0] == '~' && path[1] == '/')
			result = cd_expand_tilde(path);
		else
			result = chdir(path);
	}
	if (result == 0)
		update_directories(cwd);
	return (result);
}

static int	cd_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (-1);
	return (chdir(home));
}

static int	cd_to_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
		return (-1);
	printf("%s\n", oldpwd);
	return (chdir(oldpwd));
}

static int	cd_expand_tilde(char *path)
{
	char	*home;
	char	*full_path;
	int		result;

	home = getenv("HOME");
	if (!home)
		return (-1);
	full_path = ft_strjoin(home, path + 1);
	if (!full_path)
		return (-1);
	result = chdir(full_path);
	free(full_path);
	return (result);
}

static void	update_directories(char *old_cwd)
{
	char	new_cwd[PATH_MAX];

	if (getcwd(new_cwd, sizeof(new_cwd)) != NULL)
	{
		setenv("OLDPWD", old_cwd, 1);
		setenv("PWD", new_cwd, 1);
	}
}
