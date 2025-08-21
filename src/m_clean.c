/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_clean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:50:14 by zoum              #+#    #+#             */
/*   Updated: 2025/08/20 22:02:03 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_minishell(char **input, t_token **token, t_command **cmd,
			t_env *env)
{
	if (input && *input)
	{
		free(*input);
		*input = NULL;
	}
	if (token && *token)
	{
		ft_tokenlstclear(token);
		*token = NULL;
	}
	if (cmd && *cmd)
	{
		free_command_chain(cmd);
		*cmd = NULL;
	}
	if (env)
	{
		clear_env(&env);
		env = NULL;
	}
}

void	cleanup_and_exit(char **input, t_token **token, t_command **cmd,
			t_env *env)
{
	cleanup_minishell(input, token, cmd, env);
	exit(0);
}
