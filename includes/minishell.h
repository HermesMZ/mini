/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edobele <edobele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:42:39 by edobele           #+#    #+#             */
/*   Updated: 2025/08/08 12:42:39 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <string.h>
# include <stddef.h>
# include <errno.h>
# include <stddef.h>

typedef struct s_pipe_data
{
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
	int		is_piped;
	int		outfile_error;
	int		redir_in_fd;
}	t_pipe_data;

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

typedef enum e_token_type
{
	WORD,
	PIPE,
	LOGICAL_OR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NO_WORD
}	t_quote_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	t_quote_type	quote_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_token_data
{
	t_token_type	type;
	t_quote_type	quote;
	int				start;
	int				len;
}	t_token_data;

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	t_token				*cmd;
	t_token				**args;
	t_redirect			*redirects;
	int					pipe_out;
	struct s_command	*next;
}	t_command;

typedef enum e_parsing_state
{
	EXPECTING_CMD,
	EXPECTING_CMD_OR_ARG,
	EXPECTING_FILE
}	t_parsing_state;

//test
char		*get_token_type_str(t_token_type type);
char		*get_quote_type_str(t_quote_type quote);
char		*get_redirect_type_str(t_token_type type);
void		print_redirections(t_redirect *redirects);
void		print_token_arguments(t_token **args);
void		print_command_details(t_command *cmd, int cmd_count);
void		test_parsing(t_token *token);

//fonction minishell
void		handle_sigint(int signum);
int			tokenizer(char *input, t_token **token, int i);
int			is_char_symbol(char *input, t_token **token, int i);
int			is_single_quote(t_token **token, char *input, int i);
int			is_double_quote(t_token **token, char *input, int i);
int			add_new_token_word(int start, int i, t_token **token, char *input);
int			is_special_char(char c);
int			ft_isdigit(int c);
int			is_dollard(t_token **token, char *input, int i);
int			has_unclosed_quotes(char *input);
int			create_token(t_token_data data, char *input, t_token **token);
int			is_greater_than_symbol(t_token **token, char *input, int i);
int			is_less_than_symbol(t_token **token, char *input, int i);
int			is_pipe(t_token **token, char *input, int i);
int			is_token_valid(t_token *token);
int			has_leading_pipe(char *input);
int			is_redirection_syntax_valid(char *input);
void		ft_lstadd_back_command(t_command **lst, t_command *new);
t_command	*create_new_command(t_token *token);
void		free_command_chain(t_command **command);
void		free_command(t_command *cmd);
int			add_argument(t_command *current_command, t_token *token);
t_command	*parse_tokens(t_token *token);
t_command	*handle_parsing_error(t_command **commands,
				t_command *current_command);
int			is_redirection_token(t_token_type type);
int			add_redir(t_command *cmd, t_token_type type, char *filename);
void		add_redirect_to_list(t_redirect **redirects,
				t_redirect *new_redirect);
t_redirect	*create_redirection(t_token_type type, char *filename);
char		*get_token_symbol(t_token_type type);
int			handle_word_token(t_parsing_state *state, t_command **current_cmd,
				t_token *token, t_command **commands);
int			handle_word_expecting_file(t_parsing_state *state,
				t_command **current_cmd, t_token *token);
int			handle_word_expecting_arg(t_parsing_state *state,
				t_command **current_cmd, t_token *token, t_command **commands);
int			handle_word_expecting_cmd(t_parsing_state *state,
				t_command **current_cmd, t_token *token, t_command **commands);
t_command	*handle_parsing_error(t_command **cmd,
				t_command *current_command);
int			is_redirection_token(t_token_type type);
int			handle_redirection_token(t_parsing_state *state,
				t_command **current_cmd);
int			handle_pipe_token(t_parsing_state *state, t_command **current_cmd,
				t_command **commands, t_token *token);
int			process_single_token(t_token *token, t_parsing_state *state,
				t_command **current_cmd, t_command **commands);
int			validate_input_syntax(char *input);
int			process_tokens(char *input, t_token **token);
char		*handle_multiline_input(char *input);
char		*handle_multiline_input(char *input);

// main
int			has_unclosed_quotes(char *str);
int			has_trailing_pipe(char *input);
int			process_tokens(char *input, t_token **token);
int			validate_input_syntax(char *input);
char		*join_and_free(char *input, char *next_line);
void		minishell_loop(t_env **env, char *input, t_token *token);
void		execute_command(t_token **token, t_env **env);
void		init_minishell(t_env **env, char **envp);
void		minishell_loop(t_env **env, char *input, t_token *token);

// lib
char		*ft_strdup(const char *s, int len_s, int i);
int			ft_strlen(const char *s);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_tokenlstclear(t_token **lst);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
char		*ft_strjoin(const char *str1, const char *str2);
int			ft_strcmp(const char *s1, const char *s2);

//=========================== Exec ============================

t_env		*extract_env(char **envp);
void		clear_env(t_env **env);
void		add_env_node(t_env *env, t_env_node *new_node);
void		remove_env_node(t_env *env, t_env_node *node);
t_env_node	*create_env_node(t_env *env, char *key, char *value);
t_env_node	*get_env(t_env *env, const char *key);

int			handle_pwd(void);
int			handle_cd(t_env *env, t_command *command);
int			handle_unset(t_env *env, t_command *command);
int			handle_env(t_env *env);
int			handle_echo_n(t_command *command);
int			handle_exit(t_command *command, t_env *env);
int			handle_echo_n(t_command *command);
int			handle_export(t_env *env, t_command *command);
int			print_export(t_env *env);

int			exec_builtins(t_command *commands, t_env *env);
int			pipexecution(t_env *env, t_command *cmd);
int			exec_child(t_env *env, t_command *command, t_pipe_data *pipe_data);


// Command validation
int			check_command(t_env *env, t_command *cmd);

void		setup_input_redirect(int in_fd);
int			setup_output_redirect(t_command *command, int pipe_fd[2],
				char *outfile);

void		handle_command_error(t_command *command, int check_result);
void		handle_system_error(const char *error_msg);

int			fork_and_exec(t_env *env, t_command *command,
				t_pipe_data *pipe_data);
int			wait_for_children(void);

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

// Cleanup functions
void		cleanup_minishell(char **input, t_token **token, t_command **cmd, t_env *env);
void		cleanup_and_exit(char **input, t_token **token, t_command **cmd, t_env *env);

#endif /* MINISHELL_H */