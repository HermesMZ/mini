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

typedef enum e_token_type
{
	WORD,
	PIPE, // |
	LOGICAL_OR, // ||
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	HEREDOC, // <<
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
}   t_redirect;

typedef struct s_command
{
    t_token				*cmd;           // ls, grep, etc...
    t_token				**args;        // -a, -e etc...
    t_redirect			*redirects;     // liste des redirections
    int					pipe_out;       // 1 si il y a une pipe après la commande sinon 0
    struct s_command	*next;
} t_command;

typedef enum e_parsing_state
{
    EXPECTING_CMD,
    EXPECTING_CMD_OR_ARG,
    EXPECTING_FILE
} t_parsing_state;

//test
char	*get_token_type_str(t_token_type type);
char	*get_quote_type_str(t_quote_type quote);
char	*get_redirect_type_str(t_token_type type);
void	print_redirections(t_redirect *redirects);
void	print_token_arguments(t_token **args);
void	print_command_details(t_command *cmd, int cmd_count);
void	test_parsing(t_token *token);

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
t_command	*handle_parsing_error(t_command **commands, t_command *current_command);
int			is_redirection_token(t_token_type type);
int			add_redir(t_command *cmd, t_token_type type, char *filename);
void		add_redirect_to_list(t_redirect **redirects, t_redirect *new_redirect);
t_redirect	*create_redirection(t_token_type type, char *filename);
char		*get_token_symbol(t_token_type type);

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

#endif /* MINISHELL_H */