#include "minishell.h"
#include "m_minishell.h"

volatile sig_atomic_t g_interrupted = 0;

void	handle_sigint(int signum)
{
	(void)signum;

	g_interrupted = 1;
	write(1, "\n", 1);
    rl_replace_line("", 0); // del la lign de l'historique
	rl_on_new_line(); // dit a l'histo qu'on est sur une newline
	rl_redisplay(); // reaffiche minishell$
}
int	has_unclosed_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}
int	has_trailing_pipe(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = ft_strlen(input);
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i--;
	if (i >= 0 && input[i] == '|')
		return (1);
	return (0);
}
int	has_leading_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|' && input[i + 1] && input[i + 1] == '|')
	{
		printf("Minishell : syntax error near unexpected token `||'\n");
		return (1);
	}
	if (input[i] == '|')
	{
		add_history(input);
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
int main(int argc, char *argv[], char **envp)
{
    char    	*input;
	t_token 	*token;
	char 		*next_line;
	char		*joined;
	t_command	*cmd;
	t_env		*env;

	env = NULL;
	env = extract_env(envp, &env);
	// pour éviter l’avertissement de variable non utilisée
    (void)argc;
    (void)argv;

	token = NULL;
	cmd = NULL;
    signal(SIGINT, handle_sigint); // gère ctrl-c
    signal(SIGQUIT, SIG_IGN); // gère ctrl-/
    while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			// write(1, "exit\n", 5);
			break;
		}
			if (has_leading_pipe(input) || is_redirection_syntax_valid(input))
			{
				add_history(input);
				free(input);
				continue;
			}
			while (has_unclosed_quotes(input) || has_trailing_pipe(input))
			{
				next_line = readline("> ");
				if (g_interrupted)
				{
					free(input);
					input = ft_strdup("", 0, 0);
					g_interrupted = 0;
					break;
				}
				if (!next_line)
				{
					free(input);
					input = ft_strdup("", 0, 0);
					continue;
				}
				joined = ft_strjoin(input, "\n");
				free(input);
				input = ft_strjoin(joined, next_line);
				free(joined);
				free(next_line);
			}
			if (!input)
				continue;
			if (!tokenizer(input, &token, 0))
			{
				free(input);
				continue;
			}
			if (!is_token_valid(token))
			{
				add_history(input);
				free(input);
				ft_tokenlstclear(&token);
				continue;
			}
			test_parsing(token);
			cmd = parse_tokens(token);
			exec(cmd, &env, &token);
			add_history(input);
			if (input)
				free(input);
			if (token)
				ft_tokenlstclear(&token);
		}
		clear_env(&env);

		return (0);
	}
