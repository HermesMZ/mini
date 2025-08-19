/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtin_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:24:54 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 18:00:23 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

static int	cd_to_home(t_env **env);
static int	cd_to_oldpwd(t_env **env);
static int	cd_expand_tilde(t_env **env, char *path);
static void	update_oldpwd(t_env **env, char *old_pwd);

int	handle_cd(t_env **env, t_command *command)
{
	char	*path;
	char	pwd[PATH_MAX];
	int		result;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (-1);
	if (!command->args || !command->args[0] || !command->args[0]->string
		|| command->args[0]->string[0] == '\0')
		result = cd_to_home(env);
	else
	{
		path = command->args[0]->string;
		if (ft_strcmp(path, "~") == 0)
			result = cd_to_home(env);
		else if (ft_strcmp(path, "-") == 0)
			result = cd_to_oldpwd(env);
		else if (path[0] == '~' && path[1] == '/')
			result = cd_expand_tilde(env, path);
		else
			result = chdir(path);
	}
	printf("%d\n", result);
	if (result == 0)
		update_oldpwd(env, pwd);
	return (result);
}

static int	cd_to_home(t_env **env)
{
	t_env_node	*home_node;

	home_node = get_env(*env, "HOME");
	if (!home_node || !home_node->value)
	{
		printf("Minishell: cd: HOME not set\n");
		return (-1);
	}
	return (chdir(home_node->value));
}

static int	cd_to_oldpwd(t_env **env)
{
	t_env_node	*oldpwd_node;

	oldpwd_node = get_env(*env, "OLDPWD");
	if (!oldpwd_node || !oldpwd_node->value)
	{
		printf("Minishell: cd: OLDPWD not set\n");
		return (-1);
	}
	printf("%s=%s\n", oldpwd_node->key, oldpwd_node->value);
	return (chdir(oldpwd_node->value));
}

static int	cd_expand_tilde(t_env **env, char *path)
{
	t_env_node	*home_node;
	char		*full_path;
	int			result;

	home_node = get_env(*env, "HOME");
	if (!home_node || !home_node->value)
		return (-1);
	full_path = ft_strjoin(home_node->value, path + 1);
	if (!full_path)
		return (-1);
	result = chdir(full_path);
	free(full_path);
	return (result);
}

static void	update_oldpwd(t_env **env, char *old_pwd)
{
	t_env_node	*oldpwd_node;
	char		*new_value;

	if (!env || !*env || !old_pwd)
		return ;

	oldpwd_node = get_env(*env, "OLDPWD");
	if (oldpwd_node)
	{
		new_value = ft_strdup(old_pwd, ft_strlen(old_pwd), 0);
		if (!new_value)
			return ;
		if (oldpwd_node->value)
			free(oldpwd_node->value);
		oldpwd_node->value = new_value;
	}
	else
		create_env_node(env, "OLDPWD", old_pwd);
}
