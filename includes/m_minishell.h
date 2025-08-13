/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/13 17:33:03 by mzimeris         ###   ########.fr       */
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

t_env	*extract_env(char **envp, t_env **env);
void	clear_env(t_env **env);
void	add_env_node(t_env **env, t_env *node);
void	remove_env_node(t_env **env, t_env *node);
void	create_env_node(t_env **env, char *key, char *value);

int		handle_export(t_env **env, t_command *command);
int		handle_unset(t_env **env, t_command *command);
int		handle_env(t_env *env);
int		print_export(t_env **env);

int		handle_echo(t_command *command);

void	debug_print_token(t_token *token);
void	debug_print_all_tokens(t_token *token);

int		exec(t_command *commands, t_env **env, t_token **token);
int		exec_builtins(t_command *commands, t_env **env, t_token **token);

int		handle_pwd(void);
int		handle_cd(t_command *command);

void	run_test_commands(char **envp);

void	free_splitted(char **splitted);
char	**ft_split(const char *s, char c);


#endif /* M_MINISHELL_H */