#include "minishell.h"

char	*join_and_free(char *input, char *next_line)
{
	char	*joined;
	char	*temp;

	joined = ft_strjoin(input, "\n");
	free(input);
	temp = ft_strjoin(joined, next_line);
	free(joined);
	return (temp);
}

int	validate_input_syntax(char *input)
{
	if (has_leading_pipe(input) || is_redirection_syntax_valid(input))
	{
		add_history(input);
		return (0);
	}
	return (1);
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
void	execute_command(t_token **token, t_env **env)
{
	t_command	*cmd;

	cmd = parse_tokens(*token);
	pipexecution(*env, cmd);
	if (cmd)
		free_command_chain(&cmd);
}
