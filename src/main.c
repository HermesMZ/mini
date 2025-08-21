#include "../includes/minishell.h"

volatile sig_atomic_t g_interrupted = 0;

void	handle_sigint(int signum)
{
	(void)signum;
	g_interrupted = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*handle_multiline_input(char *input)
{
	char	*next_line;

	while (has_unclosed_quotes(input) || has_trailing_pipe(input))
	{
		next_line = readline("> ");
		if (g_interrupted)
		{
			free(input);
			input = ft_strdup("", 0, 0);
			g_interrupted = 0;
			break ;
		}
		if (!next_line)
		{
			free(input);
			input = ft_strdup("", 0, 0);
			break ;
		}
		input = join_and_free(input, next_line);
		free(next_line);
	}
	return (input);
}

void	init_minishell(t_env **env, char **envp)
{
	*env = extract_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_loop(t_env **env, char *input, t_token *token)
{
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!validate_input_syntax(input))
		{
			free(input);
			continue ;
		}
		input = handle_multiline_input(input);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (process_tokens(input, &token))
		{
			test_parsing(token);
			execute_command(&token, env);
			add_history(input);
		}
		free(input);
		if (token)
			ft_tokenlstclear(&token);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	char	*input;
	t_token	*token;

	(void)argc;
	(void)argv;
	env = NULL;
	token = NULL;
	input = NULL;
	init_minishell(&env, envp);
	minishell_loop(&env, input, token);
	clear_env(&env);
	return (0);
}
