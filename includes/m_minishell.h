/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:12:43 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 19:01:45 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_MINISHELL_H
# define M_MINISHELL_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <unistd.h>

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	char				**path;
	char				**envp;
	struct s_env_node	*env_list;
	int					last_exit_status;
	int					last_pid;
}	t_env;

t_env		*extract_env(char **envp, t_env **env);
void		clear_env(t_env **env);
void		add_env_node(t_env **env, t_env_node *new_node);
void		remove_env_node(t_env **env, t_env_node *node);
void		create_env_node(t_env **env, char *key, char *value);
t_env_node	*get_env(t_env *env, const char *key);

int			handle_pwd(void);
int			handle_cd(t_env **env, t_command *command);
int			handle_unset(t_env **env, t_command *command);
int			handle_env(t_env *env);
int			handle_echo_n(t_command *command);
int			handle_exit(t_command *command, t_env **env);
int			handle_echo_n(t_command *command);
int			handle_export(t_env **env, t_command *command);
int			print_export(t_env **env);

int			exec(t_command *commands, t_env **env, t_token **token);
int			exec_builtins(t_command *commands, t_env **env);
int			exec_system(t_command *command, t_env **env, char *outfile);
int			pipexecution(t_env **env, t_command **cmd, char *infile,
				char *outfile);

// Command validation
int			check_command(t_env *env, t_command *cmd);

void		setup_input_redirect(int in_fd);
int			setup_output_redirect(t_command *command, int pipe_fd[2],
				char *outfile);

void		handle_command_error(t_command *command, int check_result);
void		handle_system_error(const char *error_msg);

int			fork_and_exec(t_env **env, t_command *command, int in_fd,
				char *outfile);
int			wait_for_children(pid_t last_pid);


void		debug_print_token(t_token *token);
void		debug_print_all_tokens(t_token *token);
void		debug_print_env(t_env *env);


void		run_test_commands(char **envp);

void		free_splitted(char **splitted);
char		**ft_split(const char *s, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t dsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dsize);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);


#endif /* M_MINISHELL_H */