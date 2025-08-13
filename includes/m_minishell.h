/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:12:43 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 14:13:55 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_MINISHELL_H
# define M_MINISHELL_H

# include "minishell.h"
# include <linux/limits.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*extract_env(char **envp);

int		handle_export(t_env *env, char *key, char *value);
int		handle_unset(t_env *env, char *key);
int		handle_env(t_env *env);

void	debug_print_token(t_token *token);
void	debug_print_all_tokens(t_token *token);

int		exec(t_command *commands, char **envp);
int		exec_builtins(t_command *commands, t_env *env);

int		handle_pwd(void);
int		handle_cd(t_command *commands);

void	run_test_commands(char **envp);

#endif /* M_MINISHELL_H */